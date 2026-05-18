#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"
#include <juce_dsp/juce_dsp.h>
#include <atomic>

class ChorusEffect : public AbstractEffect {
public:
    ChorusEffect();
    ~ChorusEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override;
    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] juce::String getEffectType() const override { return "ChorusEffect"; }

    [[nodiscard]] juce::var toJSON() const override;
    void fromJSON(const juce::var &json) override;

    float getDepth() const;
    float getRate() const;
    float getMix() const;

    void setRate(float newRate);
    void setDepth(float newDepth);
    void setCentreDelay(float newCentreDelay);
    void setFeedback(float newFeedback);
    void setMix(float newMix);
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

private:
    void syncParameters();

    juce::dsp::Chorus<float> chorus;

    std::atomic<float> rate { 1.5f };
    std::atomic<float> depth { 0.5f };
    std::atomic<float> centreDelay { 7.0f };
    std::atomic<float> feedback { 0.2f };
    std::atomic<float> mix { 0.5f };
};
