#pragma once

#include "TuningState.h"

#include <JuceHeader.h>
#include <string>
#include <vector>

/**
 * @brief UI-only tuner view. Reads TuningState published by AudioEngine.
 */
class ChromaticTunerComponent : public juce::Component,
                                private juce::Timer
{
public:
    explicit ChromaticTunerComponent(TuningState& tuningState);
    ~ChromaticTunerComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void timerCallback() override;
    static std::string noteNameForMidi(int midiNote);

    TuningState& tuningState;

    std::string currentNote { "No Signal" };
    float currentTuneCents = 0.0f;
    bool isInTune = false;

    static const std::vector<std::string> notesNames;
};
