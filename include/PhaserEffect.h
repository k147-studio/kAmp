#pragma once

#include "AbstractEffect.h"

#include <juce_dsp/juce_dsp.h>

#include <atomic>

class PhaserEffect : public AbstractEffect
{
public:
    PhaserEffect();
    ~PhaserEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] juce::String getEffectType() const override { return "PhaserEffect"; }

    [[nodiscard]] juce::var toJSON() const override;
    void fromJSON(const juce::var& json) override;

    float getRate() const;
    float getDepth() const;
    float getCentreFrequency() const;
    float getFeedback() const;
    float getMix() const;

    void setRate(float value);
    void setDepth(float value);
    void setCentreFrequency(float value);
    void setFeedback(float value);
    void setMix(float value);

private:
    void syncParameters();

    juce::dsp::Phaser<float> phaser;

    std::atomic<float> rate { 1.0f };
    std::atomic<float> depth { 0.5f };
    std::atomic<float> centreFrequency { 1300.0f };
    std::atomic<float> feedback { 0.0f };
    std::atomic<float> mix { 0.5f };
};
