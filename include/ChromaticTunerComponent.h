#pragma once

#include <JuceHeader.h>

#include "ChromaticTuner.h"

struct ChromaticTuningResult
{
    std::string noteName;
    float frequency;
    float deviation;
    bool isInTune;
};

class ChromaticTunerComponent : public juce::Component
{
public:
    explicit  ChromaticTunerComponent(int sampleRate = 44100, int fftOrder = 10);
    ~ChromaticTunerComponent() override;

    void paint(juce::Graphics &g) override;
    void resized() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void tune(const AudioSourceChannelInfo &bufferToFill);
    bool isTuning();
private:
    ChromaticTuner* tuner;
    bool isTunerActive = false;
    const std::vector<std::string> notesNames;
    float baseFrequency;
    std::string currentNote;
    float currentTuneCents;
    bool isInTune;

    ChromaticTuningResult detectTuning(float frequency);
    std::string getNoteName(int midiNote);
    void updateTuningDisplay(const ChromaticTuningResult& result);
};