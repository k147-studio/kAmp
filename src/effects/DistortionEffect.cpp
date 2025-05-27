#include "DistortionEffect.h"

// Lien de la doc : https://juce.com/tutorials/tutorial_dsp_convolution/

/**
 * @brief Initializes a new instance of the DistortionEffect class.
 */
DistortionEffect::DistortionEffect() {
    // Default drive amount and mix
    effectName = "Distortion";
    drive = 1.0f;
    mix = 0.5f;
}

/**
 * @brief Destroys the instance of the DistortionEffect class.
 */
DistortionEffect::~DistortionEffect() = default;

/**
 * @brief Applies the distortion effect to the given audio buffer.
 * @param bufferToFill The audio buffer to apply the effect to.
 *
 * This implementation applies a simple hard-clipping distortion by multiplying
 * the input signal by the drive amount, then limiting it between -1.0 and 1.0.
 * Finally, it mixes the distorted (wet) signal with the original (dry) signal
 * according to the mix parameter.
 *
 * For a more advanced waveshaping approach, see:
 * https://docs.juce.com/master/structdsp_1_1WaveShaper.html
 */
void DistortionEffect::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    auto *leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto *rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    int numSamples = bufferToFill.numSamples;

    for (int i = 0; i < numSamples; ++i) {
        const float inL = leftBuffer[i];
        const float inR = rightBuffer[i];

        // Appliquer un gain d'entrée pour amplifier le signal
        const float preGain = 50.0f; // Ajustez ce gain pour contrôler l'intensité
        const float shapedL = std::tanh(inL * drive * preGain);
        const float shapedR = std::tanh(inR * drive * preGain);

        // Mélanger le signal dry et wet
        leftBuffer[i] = inL * (1.0f - mix) + shapedL * mix;
        rightBuffer[i] = inR * (1.0f - mix) + shapedR * mix;
    }
}

/**
 * @brief Sets the drive amount for the distortion effect.
 * @param driveValue The drive (gain) amount before clipping.
 */
void DistortionEffect::setDrive(float driveValue) {
    drive = driveValue;
}

/**
 * @brief Sets the mix (dry/wet) of the distortion effect.
 * @param mixValue The mix between dry and wet signal (0.0 = dry, 1.0 = wet).
 */
void DistortionEffect::setMix(float mixValue) {
    mix = mixValue;
}

/**
 * @brief Compares the effect with another given effect.
 * @param effect The effect to compare with.
 * @return True if the effect is equal to the given effect, false otherwise.
 */
bool DistortionEffect::operator==(const AbstractEffect *effect) {
    if (auto other = dynamic_cast<const DistortionEffect *>(effect)) {
        return drive == other->drive && mix == other->mix;
    }
    return false;
}

