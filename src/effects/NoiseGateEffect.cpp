#include "NoiseGateEffect.h"

NoiseGateEffect::NoiseGateEffect() {
    effectName = "Noise Gate";
}

NoiseGateEffect::~NoiseGateEffect() = default;

void NoiseGateEffect::prepare(const juce::dsp::ProcessSpec& spec) {
    sampleRate = spec.sampleRate > 0.0 ? spec.sampleRate : 44100.0;
}

void NoiseGateEffect::apply(const AudioSourceChannelInfo &bufferToFill) {
    auto *leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto *rightBuffer = bufferToFill.buffer->getNumChannels() > 1
                        ? bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample)
                        : nullptr;
    int numSamples = bufferToFill.numSamples;

    const float thresholdValue = threshold.load(std::memory_order_relaxed);
    const float attackValue = attack.load(std::memory_order_relaxed);
    const float releaseValue = release.load(std::memory_order_relaxed);

    float envelopeLeft = 0.0f;
    float envelopeRight = 0.0f;

    const float attackSamples = juce::jmax(1.0f, attackValue * static_cast<float>(sampleRate));
    const float releaseSamples = juce::jmax(1.0f, releaseValue * static_cast<float>(sampleRate));
    const float attackCoeff = std::exp(-1.0f / attackSamples);
    const float releaseCoeff = std::exp(-1.0f / releaseSamples);

    for (int i = 0; i < numSamples; ++i) {
        float inputSampleLeft = leftBuffer[i];
        float inputSampleRight = rightBuffer ? rightBuffer[i] : 0.0f;

        envelopeLeft = std::max(std::abs(inputSampleLeft), envelopeLeft * (inputSampleLeft > envelopeLeft ? attackCoeff : releaseCoeff));
        if (rightBuffer)
            envelopeRight = std::max(std::abs(inputSampleRight), envelopeRight * (inputSampleRight > envelopeRight ? attackCoeff : releaseCoeff));

        float gainLeft = envelopeLeft < thresholdValue ? 0.0f : 1.0f;
        float gainRight = rightBuffer ? (envelopeRight < thresholdValue ? 0.0f : 1.0f) : 1.0f;

        leftBuffer[i] = inputSampleLeft * gainLeft;
        if (rightBuffer) {
            rightBuffer[i] = inputSampleRight * gainRight;
        }
    }
}

void NoiseGateEffect::setThreshold(float newThreshold) {
    threshold.store(newThreshold, std::memory_order_relaxed);
}

void NoiseGateEffect::setAttack(float newAttack) {
    attack.store(newAttack, std::memory_order_relaxed);
}

void NoiseGateEffect::setRelease(float newRelease) {
    release.store(newRelease, std::memory_order_relaxed);
}

float NoiseGateEffect::getThreshold() const noexcept {
    return threshold.load(std::memory_order_relaxed);
}

float NoiseGateEffect::getAttack() const noexcept {
    return attack.load(std::memory_order_relaxed);
}

float NoiseGateEffect::getRelease() const noexcept {
    return release.load(std::memory_order_relaxed);
}

bool NoiseGateEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}
