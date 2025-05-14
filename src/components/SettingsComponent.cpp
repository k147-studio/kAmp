#include "SettingsComponent.h"

SettingsComponent::SettingsComponent(juce::AudioDeviceManager& deviceManager)
    : deviceSelector(deviceManager, 0, 2, 0, 2, true, true, false, false)
{
    addAndMakeVisible(label);
    label.setText("Settings", juce::dontSendNotification);

    addAndMakeVisible(deviceSelector);
}

void SettingsComponent::resized()
{
    label.setBounds(10, 10, getWidth() - 20, 30);
    deviceSelector.setBounds(10, 50, getWidth() - 20, getHeight() - 60);
}
