#pragma once

#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>

class SettingsComponent : public juce::Component {
public:
    explicit SettingsComponent(juce::AudioDeviceManager& deviceManager);

    void resized() override;

private:
    juce::AudioDeviceSelectorComponent deviceSelector;
};
