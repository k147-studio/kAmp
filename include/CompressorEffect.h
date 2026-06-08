#pragma once

#include "AbstractEffect.h"

#include <juce_dsp/juce_dsp.h>

#include <atomic>

class CompressorEffect : public AbstractEffect
{
public:
    CompressorEffect();
    ~CompressorEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] juce::String getEffectType() const override { return "CompressorEffect"; }

    [[nodiscard]] juce::var toJSON() const override;
    void fromJSON(const juce::var& json) override;

    float getThreshold() const;
    float getRatio() const;
    float getAttack() const;
    float getRelease() const;
    float getLevel() const;

    void setThreshold(float value);
    void setRatio(float value);
    void setAttack(float value);
    void setRelease(float value);
    void setLevel(float value);

private:
    void syncParameters();

    enum
    {
        compressorIndex,
        gainIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::Compressor<float>, juce::dsp::Gain<float>> processorChain;

    std::atomic<float> threshold { -20.0f };
    std::atomic<float> ratio { 4.0f };
    std::atomic<float> attack { 10.0f };
    std::atomic<float> release { 100.0f };
    std::atomic<float> level { 0.0f };
};
