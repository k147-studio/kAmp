#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

/**
 * @brief Interface that declares the actions an effect should be able to do.
 */
class IEffect {
  public:
    /**
     * @brief Applies the effect to the given audio buffer.
     * @param bufferToFill The audio buffer to apply the effects to.
     */
    virtual void apply(const juce::AudioSourceChannelInfo &bufferToFill) = 0;

    /**
     * @brief Destroys the current instance of IEffect.
     */
    virtual ~IEffect() = default;
};