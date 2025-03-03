#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>
#include "AbstractEffect.h"

class DelayEffect : public AbstractEffect {
    public:
        DelayEffect();
        ~DelayEffect() override;
        void apply(const juce::AudioSourceChannelInfo &bufferToFill);
        void setRate(float rate);
        void setDelay(float delay);
        bool operator==(const AbstractEffect* effect) override;
    private:
        //juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine;
        float rate;
        float delay;
};