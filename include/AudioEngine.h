#pragma once

#include "ChromaticTuner.h"
#include "Pedalboard.h"
#include "TuningState.h"

#include <atomic>
#include <memory>

/**
 * @brief Owns the pedalboard and realtime processing (effects, mute, tuner DSP).
 */
class AudioEngine
{
public:
    explicit AudioEngine(std::unique_ptr<Pedalboard> pedalboard);
    ~AudioEngine() = default;

    AudioEngine(const AudioEngine&) = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;

    Pedalboard& getPedalboard() noexcept;
    [[nodiscard]] const Pedalboard& getPedalboard() const noexcept;

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(const AudioSourceChannelInfo& bufferToFill);
    void reset();

    std::atomic<bool>& getMuteFlag() noexcept { return muted; }
    TuningState& getTuningState() noexcept { return tuningState; }

private:
    void processTuner(const AudioSourceChannelInfo& bufferToFill);
    void publishTuning(float frequency);

    std::unique_ptr<Pedalboard> pedalboard;
    std::unique_ptr<ChromaticTuner> tuner;

    std::atomic<bool> muted { false };
    TuningState tuningState;

    double sampleRate = 44100.0;
    int fftOrder = 9;
    float smoothedFrequency = 0.0f;
    float smoothingCoeff = 0.2f;
};
