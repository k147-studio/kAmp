#include "NoiseGateEffect.h"

NoiseGateEffect::NoiseGateEffect() {
    threshold = 0.5f;
    attack = 0.01f;
    release = 0.1f;
    effectName = "Noise Gate";
}

NoiseGateEffect::~NoiseGateEffect() = default;

void NoiseGateEffect::apply(const AudioSourceChannelInfo &bufferToFill) {
    auto *leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto *rightBuffer = bufferToFill.buffer->getNumChannels() > 1
                        ? bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample)
                        : nullptr;
    int numSamples = bufferToFill.numSamples;

    float envelopeLeft = 0.0f;
    float envelopeRight = 0.0f;

    float attackCoeff = std::exp(-1.0f / (attack * numSamples));
    float releaseCoeff = std::exp(-1.0f / (release * numSamples));

    for (int i = 0; i < numSamples; ++i) {
        float inputSampleLeft = leftBuffer[i];
        float inputSampleRight = rightBuffer ? rightBuffer[i] : 0.0f;

        envelopeLeft = std::max(std::abs(inputSampleLeft), envelopeLeft * (inputSampleLeft > envelopeLeft ? attackCoeff : releaseCoeff));
        if (rightBuffer)
            envelopeRight = std::max(std::abs(inputSampleRight), envelopeRight * (inputSampleRight > envelopeRight ? attackCoeff : releaseCoeff));

        float gainLeft = envelopeLeft < threshold ? 0.0f : 1.0f;
        float gainRight = rightBuffer ? (envelopeRight < threshold ? 0.0f : 1.0f) : 1.0f;

        leftBuffer[i] = inputSampleLeft * gainLeft;
        if (rightBuffer) {
            rightBuffer[i] = inputSampleRight * gainRight;
        }
    }
}

void NoiseGateEffect::setThreshold(float threshold) {
    this->threshold = threshold;
}

void NoiseGateEffect::setAttack(float attack) {
    this->attack = attack;
}

void NoiseGateEffect::setRelease(float release) {
    this->release = release;
}

bool NoiseGateEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}