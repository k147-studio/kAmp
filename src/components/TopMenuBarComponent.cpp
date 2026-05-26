#include "AccountComponent.h"
#include "AppFonts.h"
#include "BinaryData.h"
#include "ModalOverlayComponent.h"
#include "PopupContentComponent.h"
#include "ResourceManager.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"

TopMenuBarComponent::TopMenuBarComponent(AudioDeviceManager& deviceManager,
                                         std::atomic<bool>* isMuted,
                                         TuningState* tuningStatePtr)
{
    isSoundMuted = isMuted;
    tuningState = tuningStatePtr;

    setOpaque(false);
    setInterceptsMouseClicks(false, true);

    if (auto icon = ResourceManager::loadSvg(BinaryData::settings_svg, BinaryData::settings_svgSize))
        ResourceManager::configureIconButton(settingsButton, *icon);
    addAndMakeVisible(settingsButton);

    if (auto icon = ResourceManager::loadSvg(BinaryData::user_svg, BinaryData::user_svgSize))
        ResourceManager::configureIconButton(accountButton, *icon);
    addAndMakeVisible(accountButton);

    muteIcon = ResourceManager::loadSvg(BinaryData::mute_svg, BinaryData::mute_svgSize);
    unmuteIcon = ResourceManager::loadSvg(BinaryData::unmute_svg, BinaryData::unmute_svgSize);
    updateMuteButtonImage();
    addAndMakeVisible(muteButton);

    if (auto icon = ResourceManager::loadSvg(BinaryData::tuner_svg, BinaryData::tuner_svgSize))
        ResourceManager::configureIconButton(tunerButton, *icon);
    addAndMakeVisible(tunerButton);

#if !JUCE_IOS
    settingsButton.onClick = [this, &deviceManager]
    {
        openSettingsPopup(deviceManager);
    };
#endif
    accountButton.onClick = [this] { openAccountPopup(); };
    muteButton.onClick = [this] { toggleMute(); };
    tunerButton.onClick = [this] { openTunerPopup(); };

    flexBox.justifyContent = FlexBox::JustifyContent::flexEnd;
    flexBox.alignItems = FlexBox::AlignItems::center;
    flexBox.items.add(
        FlexItem(tunerButton).withWidth((float) buttonSize).withHeight((float) buttonSize)
                             .withMargin({ 0, gap, 0, 0 }));
    flexBox.items.add(
        FlexItem(muteButton).withWidth((float) buttonSize).withHeight((float) buttonSize)
                            .withMargin({ 0, gap, 0, 0 }));
    flexBox.items.add(
        FlexItem(settingsButton).withWidth((float) buttonSize).withHeight((float) buttonSize)
                                .withMargin({ 0, gap, 0, 0 }));
    flexBox.items.add(
        FlexItem(accountButton).withWidth((float) buttonSize).withHeight((float) buttonSize)
                               .withMargin({ 0, gap, 0, 0 }));
}

TopMenuBarComponent::~TopMenuBarComponent()
{
    closeAllModals();
}

void TopMenuBarComponent::paint(Graphics& g)
{
    g.setFont(AppFonts::boldItalic(24.0f));
    g.setColour(Colours::white);
    const int topMargin = (getHeight() - 24) / 2;

    g.drawText("kAmp", (int) gap, topMargin, 80, 24, Justification::left);
}

void TopMenuBarComponent::resized()
{
    if (modalOverlay != nullptr)
    {
        if (auto* mainWindow = getTopLevelComponent())
            modalOverlay->setBounds(mainWindow->getLocalBounds());
    }

    flexBox.performLayout(getLocalBounds());
}

void TopMenuBarComponent::updateMuteButtonImage()
{
    const bool muted = isSoundMuted != nullptr
        && isSoundMuted->load(std::memory_order_relaxed);

    if (const auto* icon = muted ? muteIcon.get() : unmuteIcon.get())
        ResourceManager::configureIconButton(muteButton, *icon);
}

void TopMenuBarComponent::openSettingsPopup(AudioDeviceManager& deviceManager)
{
    closeAllModals();

    settingsComponent = new SettingsComponent(deviceManager);
    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = std::make_unique<ModalOverlayComponent>(
        "Audio settings", settingsComponent, [this] { dismissModal(); });

    mainWindow->addAndMakeVisible(modalOverlay.get());
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::openAccountPopup()
{
    if (isLoggedIn)
        showAccountScreen();
    else
        openLoginPopup();
}

void TopMenuBarComponent::openLoginPopup()
{
    closeAllModals();

    loginComponent = new LoginComponent(
        [this]
        {
            isLoggedIn = true;
            closeAllModals();
            showAccountScreen();
        },
        [this] { dismissModal(); });

    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = std::make_unique<ModalOverlayComponent>(
        "Sign in", loginComponent, [this] { dismissModal(); });

    mainWindow->addAndMakeVisible(modalOverlay.get());
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::showAccountScreen()
{
    closeAllModals();

    accountComponent = new AccountComponent();
    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = std::make_unique<ModalOverlayComponent>(
        "Account", accountComponent, [this] { dismissModal(); });

    mainWindow->addAndMakeVisible(modalOverlay.get());
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::toggleMute()
{
    if (isSoundMuted == nullptr)
        return;

    const bool currentlyMuted = isSoundMuted->load(std::memory_order_relaxed);
    isSoundMuted->store(!currentlyMuted, std::memory_order_relaxed);
    updateMuteButtonImage();
}

void TopMenuBarComponent::openTunerPopup()
{
    closeAllModals();

    if (tuningState == nullptr)
        return;

    tuningState->enabled.store(true, std::memory_order_release);
    tunerComponent = new ChromaticTunerComponent(*tuningState);

    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = std::make_unique<ModalOverlayComponent>(
        "Tuner", tunerComponent, [this] { dismissModal(); });

    mainWindow->addAndMakeVisible(modalOverlay.get());
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::dismissModal()
{
    closeAllModals();
}

void TopMenuBarComponent::closeAllModals()
{
    if (modalOverlay != nullptr)
    {
        if (auto* mainWindow = getTopLevelComponent())
            mainWindow->removeChildComponent(modalOverlay.get());
    }

    if (tuningState != nullptr)
        tuningState->enabled.store(false, std::memory_order_release);

    modalOverlay.reset();

    delete settingsComponent;
    settingsComponent = nullptr;

    delete accountComponent;
    accountComponent = nullptr;

    delete loginComponent;
    loginComponent = nullptr;

    delete tunerComponent;
    tunerComponent = nullptr;
}
