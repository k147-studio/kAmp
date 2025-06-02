#include "AccountComponent.h"
#include "ModalOverlayComponent.h"
#include "PopupContentComponent.h"
#include "ResourceManager.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"

TopMenuBarComponent::TopMenuBarComponent(AudioDeviceManager &deviceManager, bool *isSoundMuted) {
    this->isSoundMuted = isSoundMuted;

    if (const Image settingsImage = ResourceManager::loadImage("resources/icons/settings.png"); settingsImage.isValid()) {
        settingsButton.setImages(true, true, true, settingsImage, 1.0f, {}, settingsImage, 1.0f, {}, settingsImage,
                                 1.0f, {});
        settingsButton.setSize(settingsImage.getWidth(), settingsImage.getHeight());
        addAndMakeVisible(settingsButton);
    } else {
        DBG("Error: image settings.png not found");
    }

    if (const Image accountImage = ResourceManager::loadImage("resources/icons/account.png"); accountImage.isValid()) {
        accountButton.setImages(true, true, true, accountImage, 1.0f, {}, accountImage, 1.0f, {}, accountImage, 1.0f,
                                {});
        accountButton.setSize(accountImage.getWidth(), accountImage.getHeight());
        addAndMakeVisible(accountButton);
    } else {
        DBG("Error: image account.png not found");
    }

    if (const Image muteImage = ResourceManager::loadImage("resources/icons/unmute.png"); muteImage.isValid()) {
        muteButton.setImages(true, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
        muteButton.setSize(muteImage.getWidth(), muteImage.getHeight());
        addAndMakeVisible(muteButton);
    } else {
        DBG("Error: image mute.png not found");
    }

    if (const Image exportImage = ResourceManager::loadImage("resources/icons/export.png"); exportImage.isValid()) {
        exportButton.setImages(true, true, true, exportImage, 1.0f, {}, exportImage, 1.0f, {}, exportImage, 1.0f, {});
        exportButton.setSize(exportImage.getWidth(), exportImage.getHeight());
        addAndMakeVisible(exportButton);
    } else {
        DBG("Error: image export.png not found");
    }

#if !JUCE_IOS
    settingsButton.onClick = [this, &deviceManager]() { openSettingsPopup(deviceManager); };
#endif
    accountButton.onClick = [this] { openAccountPopup(); };
    muteButton.onClick = [this] { toggleMute(); };
    exportButton.onClick = [] {
        DBG("export button clicked");
    };

    accountButton.setBounds(0, 0, 100, 50);
    muteButton.setBounds(0, 0, 100, 50);
    settingsButton.setBounds(0, 0, 100, 50);
    exportButton.setBounds(0, 0, 100, 50);

    flexBox.justifyContent = FlexBox::JustifyContent::flexEnd;
    flexBox.alignItems = FlexBox::AlignItems::center;
    flexBox.items.add(FlexItem(muteButton).withWidth(muteButton.getWidth()).withHeight(muteButton.getHeight()));
    flexBox.items.add(FlexItem(exportButton).withWidth(exportButton.getWidth()).withHeight(exportButton.getHeight()));
    flexBox.items.add(FlexItem(settingsButton).withWidth(settingsButton.getWidth()).withHeight(settingsButton.getHeight()));
    flexBox.items.add(FlexItem(accountButton).withWidth(accountButton.getWidth()).withHeight(accountButton.getHeight()));
}

TopMenuBarComponent::~TopMenuBarComponent() = default;

void TopMenuBarComponent::paint(Graphics &g) {
}

void TopMenuBarComponent::resized() {
    auto *mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;
    if (modalOverlay != nullptr) {
        modalOverlay->setBounds(mainWindow->getLocalBounds());
    }
    if (settingsComponent != nullptr) {
        settingsComponent->setBounds(mainWindow->getLocalBounds());
    }
    if (accountComponent != nullptr) {
        accountComponent->setBounds(mainWindow->getLocalBounds());
    }
    flexBox.performLayout(getLocalBounds());
}

void TopMenuBarComponent::openSettingsPopup(AudioDeviceManager &deviceManager) {
    settingsComponent = new SettingsComponent(deviceManager);
    auto *mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = new ModalOverlayComponent("Audio settings", settingsComponent);
    mainWindow->addAndMakeVisible(modalOverlay);
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::openAccountPopup() {
    accountComponent = new AccountComponent();
    auto *mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    modalOverlay = new ModalOverlayComponent("Account", accountComponent);
    mainWindow->addAndMakeVisible(modalOverlay);
    modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::toggleMute() {
    if (*this->isSoundMuted) {
        if (Image muteImage = ResourceManager::loadImage("resources/icons/unmute.png"); muteImage.isValid()) {
            muteButton.setImages(false, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
            addAndMakeVisible(muteButton);
        } else {
            DBG("Error: image mute.png not found");
        }
    } else {
        if (Image muteImage = ResourceManager::loadImage("resources/icons/mute.png"); muteImage.isValid()) {
            muteButton.setImages(false, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
            addAndMakeVisible(muteButton);
        } else {
            DBG("Error: image mute.png not found");
        }
    }
    *this->isSoundMuted = !*this->isSoundMuted;
}
