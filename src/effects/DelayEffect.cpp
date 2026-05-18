#include "DelayEffect.h"
#include <cmath>

DelayEffect::DelayEffect() {
    effectName = "Delay";
}

DelayEffect::~DelayEffect() = default;

void DelayEffect::resizeBuffer()
{
    const float delayMs = delay.load(std::memory_order_relaxed);

    if (delayMs <= 0.0f)
    {
        bufferCapacity = 0;
        circularBuffer.clear();
        writePosition = 0;
        return;
    }

    bufferCapacity = juce::jmax(1, static_cast<int>(std::ceil(delayMs * sampleRate / 1000.0)) + 1);
    circularBuffer.assign(static_cast<size_t>(bufferCapacity), 0.0f);
    writePosition = 0;
}

void DelayEffect::prepare(const juce::dsp::ProcessSpec& spec) {
    const juce::ScopedLock lock(bufferLock);
    sampleRate = spec.sampleRate > 0.0 ? spec.sampleRate : 44100.0;
    resizeBuffer();
}

void DelayEffect::reset() {
    const juce::ScopedLock lock(bufferLock);
    std::fill(circularBuffer.begin(), circularBuffer.end(), 0.0f);
    writePosition = 0;
}

void DelayEffect::apply(const AudioSourceChannelInfo &bufferToFill) {
    const float rateValue = rate.load(std::memory_order_relaxed);
    const float delayValue = delay.load(std::memory_order_relaxed);

    if (delayValue <= 0.0f || rateValue <= 0.0f)
        return;

    const juce::ScopedLock lock(bufferLock);

    if (bufferCapacity <= 0)
        return;

    const int numChannels = bufferToFill.buffer->getNumChannels();
    const int numSamples = bufferToFill.numSamples;
    const auto delaySamples = juce::jlimit(1, bufferCapacity,
                                           static_cast<int>(delayValue * sampleRate / 1000.0));

    if (writePosition >= delaySamples)
        writePosition %= delaySamples;

    const float feedbackGain = rateValue / 100.0f;

    for (int i = 0; i < numSamples; ++i) {
        const auto delayedSample = circularBuffer[static_cast<size_t>(writePosition)];

        for (int channel = 0; channel < numChannels; ++channel)
        {
            auto* channelBuffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
            const auto inputSample = channelBuffer[i];
            channelBuffer[i] = inputSample + delayedSample * feedbackGain;
            circularBuffer[static_cast<size_t>(writePosition)] = inputSample;
        }

        writePosition = (writePosition + 1) % delaySamples;
    }
}

void DelayEffect::setRate(const float newRate) {
    rate.store(newRate, std::memory_order_relaxed);
}

void DelayEffect::setDelay(const float newDelay) {
    delay.store(juce::jlimit(0.0f, maxDelayMs, newDelay), std::memory_order_relaxed);

    const juce::ScopedLock lock(bufferLock);
    resizeBuffer();
}

float DelayEffect::getRate() const noexcept {
    return rate.load(std::memory_order_relaxed);
}

float DelayEffect::getDelay() const noexcept {
    return delay.load(std::memory_order_relaxed);
}

bool DelayEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}
