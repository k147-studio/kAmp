#pragma once
#include <juce_audio_devices/juce_audio_devices.h>

#include <juce_audio_utils/juce_audio_utils.h>



#include <juce_gui_basics/juce_gui_basics.h>

class SettingsComponent : public juce::Component {
public:
    explicit SettingsComponent(juce::AudioDeviceManager& deviceManager)
        : deviceSelector(deviceManager, 0, 2, 0, 2, true, true, false, false)
    {
        addAndMakeVisible(label);
        label.setText("Settings", juce::dontSendNotification);

        addAndMakeVisible(deviceSelector);
    }

    void resized() override
    {
        label.setBounds(10, 10, getWidth() - 20, 30);
        deviceSelector.setBounds(10, 50, getWidth() - 20, getHeight() - 60);
    }

private:
    juce::Label label;
    juce::AudioDeviceSelectorComponent deviceSelector;
};


