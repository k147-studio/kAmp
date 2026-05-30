#pragma once

#include "AudioEngine.h"
#include "BottomMenuBarComponent.h"
#include "Manager.h"
#include "PedalboardComponent.h"
#include "TopMenuBarComponent.h"

#include <memory>

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_utils/juce_audio_utils.h>

/**
 * @brief Root UI shell. Audio processing is delegated to AudioEngine.
 */
class MainComponent final : public AudioAppComponent
{
public:
    explicit MainComponent(std::unique_ptr<Pedalboard> pedalboard);
    ~MainComponent() override;

    void paint(Graphics&) override;
    void resized() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

private:
    AudioEngine audioEngine;
    Manager manager;

    Viewport pedalboardContainer;
    PedalboardComponent pedalboardComponent;
    TopMenuBarComponent topMenuBarComponent;
    BottomMenuBarComponent bottomMenuBarComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
