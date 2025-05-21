#include "AccountComponent.h"
#include "PopupContentComponent.h"
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

