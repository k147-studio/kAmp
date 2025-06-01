#include "AccountComponent.h"
#include "PopupContentComponent.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"

#include "ModalOverlayComponent.h"
#include "ResourceManager.h"


TopMenuBarComponent::TopMenuBarComponent(juce::AudioDeviceManager& deviceManager, bool* isSoundMuted)
{
    this->isSoundMuted = isSoundMuted;


    juce::Image settingsImage = ResourceManager::loadImage("resources/icons/settings.png");
    if (settingsImage.isValid()) {
        settingsButton.setImages(true, true, true,settingsImage, 1.0f, {},settingsImage, 1.0f, {},settingsImage, 1.0f, {});
        settingsButton.setSize(settingsImage.getWidth(), settingsImage.getHeight());
        addAndMakeVisible(settingsButton);
    } else {
        DBG("Erreur : image settings.png introuvable ou invalide.");
    }

    juce::Image accountImage = ResourceManager::loadImage("resources/icons/account.png");
    if (accountImage.isValid()) {
        accountButton.setImages(true, true, true,accountImage, 1.0f, {}, accountImage, 1.0f, {},accountImage, 1.0f, {});
        accountButton.setSize(accountImage.getWidth(), accountImage.getHeight());
        addAndMakeVisible(accountButton);
    } else {
        DBG("Erreur : image account.png introuvable ou invalide.");
    }

    juce::Image muteImage = ResourceManager::loadImage("resources/icons/unmute.png");
    if (muteImage.isValid()) {
        muteButton.setImages(true, true, true, muteImage, 1.0f, {},  muteImage, 1.0f, {}, muteImage, 1.0f, {});
        muteButton.setSize(muteImage.getWidth(), muteImage.getHeight());
        addAndMakeVisible(muteButton);
    } else {
        DBG("Erreur : image mute.png introuvable ou invalide.");
    }


    #if !JUCE_IOS
        settingsButton.onClick = [this, &deviceManager]() { openSettingsPopup(deviceManager); };
    #endif
    accountButton.onClick = [this]() { openAccountPopup(); };
    muteButton.onClick = [this]() { toggleMute(); };

    settingsButton.setBounds(0, 0, 100, 50);
    accountButton.setBounds(0, 0, 100, 50);
    muteButton.setBounds(0, 0, 100, 50);
    flexBox.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
    flexBox.alignItems = juce::FlexBox::AlignItems::center;
    flexBox.items.add(
        juce::FlexItem(muteButton).withWidth(muteButton.getWidth()).withHeight(muteButton.getHeight()));
    flexBox.items.add(
        juce::FlexItem(settingsButton).withWidth(settingsButton.getWidth()).withHeight(settingsButton.getHeight()));
    flexBox.items.add(
        juce::FlexItem(accountButton).withWidth(accountButton.getWidth()).withHeight(accountButton.getHeight()));
}

TopMenuBarComponent::~TopMenuBarComponent() = default;

void TopMenuBarComponent::paint(juce::Graphics& g)
{
}


void TopMenuBarComponent::resized()
{
    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;
    if (modalOverlay != nullptr)
    {
        modalOverlay->setBounds(mainWindow->getLocalBounds());
    }
    if (settingsComponent != nullptr)
    {
        settingsComponent->setBounds(mainWindow->getLocalBounds());
    }
    if (accountComponent != nullptr)
    {
        accountComponent->setBounds(mainWindow->getLocalBounds());
    }
    flexBox.performLayout(getLocalBounds());
}

void TopMenuBarComponent::openSettingsPopup(juce::AudioDeviceManager& deviceManager)
{
    settingsComponent = new SettingsComponent(deviceManager);
    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = new ModalOverlayComponent("Audio settings", settingsComponent);
    mainWindow->addAndMakeVisible(modalOverlay);
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::openAccountPopup()
{
    accountComponent = new AccountComponent();
    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = new ModalOverlayComponent("Account", accountComponent);
    mainWindow->addAndMakeVisible(modalOverlay);
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::toggleMute()
{
    if (*this->isSoundMuted)
    {
        juce::Image muteImage = ResourceManager::loadImage("resources/icons/unmute.png");
        if (muteImage.isValid()) {
            muteButton.setImages(false, true, true, muteImage, 1.0f, {},  muteImage, 1.0f, {}, muteImage, 1.0f, {});
            addAndMakeVisible(muteButton);
        } else {
            DBG("Erreur : image mute.png introuvable ou invalide.");
        }
    }
    else
    {
        juce::Image muteImage = ResourceManager::loadImage("resources/icons/mute.png");
        if (muteImage.isValid()) {
            muteButton.setImages(false, true, true, muteImage, 1.0f, {},  muteImage, 1.0f, {}, muteImage, 1.0f, {});
            addAndMakeVisible(muteButton);
        } else {
            DBG("Erreur : image mute.png introuvable ou invalide.");
        }
    }
    *(this->isSoundMuted) = !(*(this->isSoundMuted));
}
