#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"
#include <juce_dsp/juce_dsp.h>

class ChorusEffect : public AbstractEffect {
public:
    ChorusEffect();
    ~ChorusEffect() override = default;

    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override;
    /**
     * Prepares the chorus effect for processing with the given process specification.
     * @param spec The process specification containing sample rate, block size, and number of channels.
     */
    void prepare(const juce::dsp::ProcessSpec& spec) override;
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
    void prepare(double sampleRate, int samplesPerBlock, int numChannels);


private:
    juce::dsp::Chorus<float> chorus;

    float rate = 1.5f;
    float depth = 0.5f;
    float centreDelay = 7.0f;
    float feedback = 0.2f;
    float mix = 0.5f;

    void updateParameters();
};
