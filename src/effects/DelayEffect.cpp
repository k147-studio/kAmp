#include "DelayEffect.h"

DelayEffect::DelayEffect() {
    rate = 50.0;
    delay = 500.0;
}

DelayEffect::~DelayEffect() = default;

void DelayEffect::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    auto* leftBuffer = bufferToFill.buffer->getWritePointer(0);
    auto* rightBuffer = bufferToFill.buffer->getNumChannels() > 1
                        ? bufferToFill.buffer->getWritePointer(1)
                        : nullptr;
    auto numSamples = bufferToFill.numSamples;

    auto sampleRate = 44100.0;
    auto delaySamples = static_cast<int>(delay * sampleRate / 1000.0f);

    if (circularBuffer.size() < delaySamples) {
        circularBuffer.resize(delaySamples, 0.0f);
        writePosition = 0;
    }

    for (int i = 0; i < numSamples; ++i) {
        auto delayedSample = circularBuffer[writePosition];

        auto inputSampleLeft = leftBuffer[i];
        leftBuffer[i] = inputSampleLeft + delayedSample * (rate / 100.0f);

        if (rightBuffer) {
            auto inputSampleRight = rightBuffer[i];
            rightBuffer[i] = inputSampleRight + delayedSample * (rate / 100.0f);
        }

        circularBuffer[writePosition] = inputSampleLeft;

        writePosition = (writePosition + 1) % delaySamples;
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