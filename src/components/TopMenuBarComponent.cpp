#include "AccountComponent.h"
#include "PopupWindow.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"


TopMenuBarComponent::TopMenuBarComponent(juce::AudioDeviceManager& deviceManager)
{
    settingsButton.setButtonText("Settings");
    accountButton.setButtonText("Account");
    addAndMakeVisible(settingsButton);
    addAndMakeVisible(accountButton);

    settingsButton.onClick = [this, &deviceManager]() { openSettingsPopup(deviceManager); };
    accountButton.onClick = [this]() { openAccountPopup(); };
}

TopMenuBarComponent::~TopMenuBarComponent() = default;

void TopMenuBarComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
}


void TopMenuBarComponent::resized()
{
    flexBox.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
    flexBox.alignItems = juce::FlexBox::AlignItems::center;

    settingsButton.setBounds(0, 0, 100, 50);
    accountButton.setBounds(0, 0, 100, 50);

    flexBox.items.add(
        juce::FlexItem(settingsButton).withWidth(settingsButton.getWidth()).withHeight(settingsButton.getHeight()));
    flexBox.items.add(
        juce::FlexItem(accountButton).withWidth(accountButton.getWidth()).withHeight(accountButton.getHeight()));
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
