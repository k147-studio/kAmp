#pragma once

#include "AbstractEffect.h"

#include <juce_dsp/juce_dsp.h>

#include <atomic>

class ReverbEffect : public AbstractEffect
{
public:
    ReverbEffect();
    ~ReverbEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] juce::String getEffectType() const override { return "ReverbEffect"; }

    [[nodiscard]] juce::var toJSON() const override;
    void fromJSON(const juce::var& json) override;

    float getMix() const;
    float getSize() const;
    float getDamp() const;
    float getWidth() const;

    void setMix(float value);
    void setSize(float value);
    void setDamp(float value);
    void setWidth(float value);

private:
    void syncParameters();

    juce::dsp::Reverb reverb;

    std::atomic<float> mix { 0.5f };
    std::atomic<float> size { 0.5f };
    std::atomic<float> damp { 0.5f };
    std::atomic<float> width { 1.0f };
};
