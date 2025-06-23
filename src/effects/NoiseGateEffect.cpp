#include "NoiseGateEffect.h"

NoiseGateEffect::NoiseGateEffect() {
    threshold = 0.5f;
    attack = 0.01f;
    release = 0.1f;
    effectName = "Noise Gate";
}

NoiseGateEffect::~NoiseGateEffect() = default;

void NoiseGateEffect::prepare(const juce::dsp::ProcessSpec& spec) {
}

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

    // Paramètres du filtre passe-haut simple (RC)
    float cutoff = 120.0f; // Fréquence de coupure en Hz (à ajuster)
    float sampleRate = 44100.0f; // À remplacer par la vraie valeur si possible
    float RC = 1.0f / (2.0f * float_Pi * cutoff);
    float alpha = RC / (RC + 1.0f / sampleRate);

    float prevLeft = 0.0f, prevFilteredLeft = 0.0f;
    float prevRight = 0.0f, prevFilteredRight = 0.0f;

    for (int i = 0; i < numSamples; ++i) {
        // Filtrage passe-haut
        float filteredLeft = alpha * (prevFilteredLeft + leftBuffer[i] - prevLeft);
        prevLeft = leftBuffer[i];
        prevFilteredLeft = filteredLeft;

        float inputSampleLeft = filteredLeft;

        float inputSampleRight = 0.0f;
        if (rightBuffer) {
            float filteredRight = alpha * (prevFilteredRight + rightBuffer[i] - prevRight);
            prevRight = rightBuffer[i];
            prevFilteredRight = filteredRight;
            inputSampleRight = filteredRight;
        }

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