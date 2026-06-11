#pragma once

#include "AbstractEffect.h"

#include <juce_dsp/juce_dsp.h>

#include <atomic>

class TremoloEffect : public AbstractEffect
{
public:
    TremoloEffect();
    ~TremoloEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] juce::String getEffectType() const override { return "TremoloEffect"; }

    [[nodiscard]] juce::var toJSON() const override;
    void fromJSON(const juce::var& json) override;

    float getRate() const;
    float getDepth() const;

    void setRate(float value);
    void setDepth(float value);

private:
    void syncParameters();

    juce::dsp::Oscillator<float> lfo;

    std::atomic<float> rate { 4.0f };
    std::atomic<float> depth { 0.5f };
};
