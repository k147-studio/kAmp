#include "DelayEffect.h"

DelayEffect::DelayEffect() {
    rate = 50.0;
    delay = 500.0;
    effectName = "Delay";
}

DelayEffect::~DelayEffect() = default;

void DelayEffect::prepare(const juce::dsp::ProcessSpec& spec) {
    this->sampleRate = spec.sampleRate;
}

void DelayEffect::apply(const AudioSourceChannelInfo &bufferToFill) {
    if (delay > 0 && rate > 0) {
        const int numChannels = bufferToFill.buffer->getNumChannels();
        const int numSamples = bufferToFill.numSamples;
        const auto delaySamples = static_cast<int>(delay * this->sampleRate / 1000.0f);

        if (circularBuffer.size() < delaySamples) {
            circularBuffer.resize(delaySamples, 0.0f);
            writePosition = 0;
        }


        for (int i = 0; i < numSamples; ++i) {
            auto delayedSample = circularBuffer[writePosition];
            for (int channel = 0; channel < numChannels; ++channel)
            {
                auto* channelBuffer = bufferToFill.buffer->getWritePointer(channel);
                auto inputSample = channelBuffer[i];
                channelBuffer[i] = inputSample + delayedSample * (rate / 100.0f);
                circularBuffer[writePosition] = inputSample;
            }
            writePosition = (writePosition + 1) % delaySamples;
        }
    }
}

void DelayEffect::setRate(const float rate) {
    this->rate = rate;
}

void DelayEffect::setDelay(const float delay) {
    this->delay = delay;
}

bool DelayEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}
