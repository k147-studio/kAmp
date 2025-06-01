#include "SettingsComponent.h"

SettingsComponent::SettingsComponent(juce::AudioDeviceManager& deviceManager)
    : deviceSelector(deviceManager, 0, 2, 0, 2, true, true, false, false)
{
    addAndMakeVisible(deviceSelector);
}

void SettingsComponent::resized()
{
    deviceSelector.setBounds(10, 50, getWidth() - 20, getHeight() - 60);
}
