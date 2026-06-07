#pragma once

#include "AbstractEffect.h"

#include <juce_dsp/juce_dsp.h>

#include <atomic>

class AutoWahEffect : public AbstractEffect
{
public:
    AutoWahEffect();
    ~AutoWahEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] juce::String getEffectType() const override { return "AutoWahEffect"; }

    [[nodiscard]] juce::var toJSON() const override;
    void fromJSON(const juce::var& json) override;

    float getSensitivity() const;
    float getRange() const;
    float getResonance() const;
    float getMix() const;

    void setSensitivity(float value);
    void setRange(float value);
    void setResonance(float value);
    void setMix(float value);

private:
    void syncParameters();

    juce::dsp::BallisticsFilter<float> envelope;
    juce::dsp::StateVariableTPTFilter<float> filter;

    std::atomic<float> sensitivity { 0.5f };
    std::atomic<float> range { 0.7f };
    std::atomic<float> resonance { 0.5f };
    std::atomic<float> mix { 1.0f };

    static constexpr float minCutoffHz = 300.0f;
    static constexpr float maxCutoffHz = 3000.0f;
};
