#include "AccountComponent.h"
#include "PopupContentComponent.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"
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



    settingsButton.onClick = [this, &deviceManager]() { openSettingsPopup(deviceManager); };
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
    flexBox.performLayout(getLocalBounds());
}

void TopMenuBarComponent::openSettingsPopup(juce::AudioDeviceManager& deviceManager)
{
    auto* settings = new SettingsComponent(deviceManager);
    settings->setSize(600, 400);

    juce::DialogWindow::LaunchOptions options;
    options.content.setOwned(settings); // prend possession et s'occupe de la mémoire
    options.dialogTitle = "Settings";
    options.componentToCentreAround = getTopLevelComponent(); // ou autre
    options.useNativeTitleBar = true;
    options.resizable = false;
    options.launchAsync(); // modal async
}

void TopMenuBarComponent::openAccountPopup()
{
    auto* account = new AccountComponent();
    account->setSize(600, 400);

    juce::DialogWindow::LaunchOptions options;
    options.content.setOwned(account);
    options.dialogTitle = "Account";
    options.componentToCentreAround = getTopLevelComponent();
    options.useNativeTitleBar = true;
    options.resizable = false;
    options.launchAsync();
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
