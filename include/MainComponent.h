#pragma once

#include "BottomMenuBarComponent.h"
#include "ConnectionComponent.h"
#include "Manager.h"
#include "PedalboardComponent.h"
#include "TopMenuBarComponent.h"

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

/**
 * @brief The main component of the application that contains all the main UI.
 * It is responsible for the layout of the components and the audio processing.
 * It contains the pedalboard, the top menu bar, the bottom menu bar and the connection component.
 */
class MainComponent final : public juce::AudioAppComponent {
public:
    explicit MainComponent(const Manager &manager);

    /**
     * Determines how the component is displayed.
     */
    void paint(juce::Graphics &) override;

    /**
     * Determines what to do when the component is resized.
     * Sets the sizes of the subcomponents.
     */
    void resized() override;

    /**
     * @brief Prepares the application to process audio.
     * @param samplesPerBlockExpected The number of samples per processed block expected.
     * @param sampleRate The expected sample rate.
     */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /**
     * Releases the audio sources used when the application is closed.
     * It avoids audio glitches on the operating system that can happen
     * when some resources are not released.
     */
    void releaseResources() override;

    /**
     * @brief Gets the next audio block to process.
     * @param bufferToFill The audio buffer to apply the effects to.
     */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

private:
    /**
     * The grid that contains the main components on the main page.
     */
    juce::Grid grid;

    /**
     * The component that allows the user to login.
     */
    LoginComponent connectionComponent;

    /**
     * The component that displays the pedalboard.
     */
    PedalboardComponent pedalboardComponent;

    /**
     * The menu bar at the top of the application.
     */
    TopMenuBarComponent topMenuBarComponent;

    /**
     * The bottom menu bar of the application.
     */
    BottomMenuBarComponent bottomMenuBarComponent;

    /**
     * The manager that processes the audio stream and effects.
     */
    Manager manager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
