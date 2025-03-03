#include "DelayEffect.h"

DelayEffect::DelayEffect() {
    rate = 50.0;
    delay = 500.0;
}

DelayEffect::~DelayEffect() = default;

void DelayEffect::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    auto* leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    auto numSamples = bufferToFill.numSamples;
    auto sampleRate = bufferToFill.buffer->getNumSamples();
    auto delaySamples = delay * sampleRate / 1000;
    auto rateSamples = rate * sampleRate / 100;

    for (int i = 0; i < numSamples; i++) {
        auto delayedSample = i - delaySamples;
        if (delayedSample < 0) {
            leftBuffer[i] = leftBuffer[i] + leftBuffer[i] * rateSamples / 100;
            rightBuffer[i] = rightBuffer[i] + rightBuffer[i] * rateSamples / 100;
        } else {
            leftBuffer[i] = leftBuffer[i] + rateSamples / 100;
            rightBuffer[i] = rightBuffer[i] + rateSamples / 100;
        }
    }
}

void DelayEffect::setRate(float rate) {
    this->rate = rate;
}

void DelayEffect::setDelay(float delay) {
    this->delay = delay;
}

bool DelayEffect::operator==(const AbstractEffect* effect) {
    return true;
}