#include "AccountComponent.h"
#include "PopupWindow.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"


TopMenuBarComponent::TopMenuBarComponent(juce::AudioDeviceManager& deviceManager, bool* isSoundMuted)
{
    this->isSoundMuted = isSoundMuted;

    Image settingsImage = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/icons/settings.png")));
    settingsButton.setImages(true, true, true, settingsImage, 1.0f, {}, settingsImage, 1.0f, {}, settingsImage, 1.0f, {});

    Image accountImage = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/icons/account.png")));
    accountButton.setImages(true, true, true, accountImage, 1.0f, {}, accountImage, 1.0f, {}, accountImage, 1.0f, {});

    Image muteImage = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/icons/mute.png")));
    muteButton.setImages(true, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});

    addAndMakeVisible(settingsButton);
    addAndMakeVisible(accountButton);
    addAndMakeVisible(muteButton);

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
    new PopupWindow("Settings", settings); // auto-delete dans closeButtonPressed
}

void TopMenuBarComponent::openAccountPopup()
{
    auto* account = new AccountComponent();
    new PopupWindow("Account", account); // auto-delete dans closeButtonPressed
}

void TopMenuBarComponent::toggleMute()
{
    if (*this->isSoundMuted)
    {
        Image muteImage = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/icons/mute.png")));
        muteButton.setImages(false, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
    }
    else
    {
        Image muteImage = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/icons/unmute.png")));
        muteButton.setImages(false, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
    }
    *(this->isSoundMuted) = !(*(this->isSoundMuted));
}
