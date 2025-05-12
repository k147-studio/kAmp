#pragma once

#include "AbstractEffect.h"
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

/**
 * @brief Represents a distortion effect that applies non-linear clipping to the audio stream.
 * Inherits from the AbstractEffect class.
 */
class DistortionEffect : public AbstractEffect {
public:
    /**
     * @brief Initializes a new instance of the DistortionEffect class.
     */
    DistortionEffect();

    /**
     * @brief Destroys the instance of the DistortionEffect class.
     */
    ~DistortionEffect() override;

    /**
     * @brief Applies the distortion effect to the given audio buffer.
     * @param bufferToFill The audio buffer to apply the effect to.
     */
    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;

    /**
     * @brief Sets the drive amount for the distortion effect.
     * @param driveValue The drive (gain) amount before clipping.
     */
    void setDrive(float driveValue);

    /**
     * @brief Sets the mix (dry/wet) of the distortion effect.
     * @param mixValue The mix between dry and wet signal (0.0 = dry, 1.0 = wet).
     */
    void setMix(float mixValue);

    /**
     * @brief Compares the effect with another given effect.
     * @param effect The effect to compare with.
     * @return True if the effect is equal to the given effect, false otherwise.
     */
    bool operator==(const AbstractEffect* effect) override;

private:
    /**
     * @brief The drive amount applied before clipping.
     */
    float drive;

    /**
     * @brief The dry/wet mix of the effect.
     */
    float mix;
};
