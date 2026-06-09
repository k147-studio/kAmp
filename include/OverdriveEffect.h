#pragma once

#include "AbstractEffect.h"

#include <juce_dsp/juce_dsp.h>

#include <atomic>
#include <cmath>

class OverdriveEffect : public AbstractEffect
{
public:
    OverdriveEffect();
    ~OverdriveEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] juce::String getEffectType() const override { return "OverdriveEffect"; }

    [[nodiscard]] juce::var toJSON() const override;
    void fromJSON(const juce::var& json) override;

    float getDrive() const;
    float getTone() const;
    float getLevel() const;

    void setDrive(float value);
    void setTone(float value);
    void setLevel(float value);

private:
    struct SoftClipShaper
    {
        float* drive = nullptr;

        float operator()(float x) const noexcept
        {
            return std::tanh((*drive) * x);
        }
    };

    using Filter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                                  juce::dsp::IIR::Coefficients<float>>;

    void syncParameters();
    void updateTone(float toneValue);

    juce::dsp::ProcessorChain<
        Filter,                                          // high-pass ~80 Hz
        Filter,                                          // peaking mid ~720 Hz
        juce::dsp::WaveShaper<float, SoftClipShaper>,    // soft clip
        Filter,                                          // tone low-pass
        juce::dsp::Gain<float>                           // level
    > processorChain;

    std::atomic<float> drive { 0.5f };
    std::atomic<float> tone { 0.5f };
    std::atomic<float> level { 0.7f };

    float audioDrive = 1.0f;
    float audioTone = -1.0f;
    double sampleRate = 44100.0;
};
