#pragma once

#include "AbstractEffect.h"
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

/**
 * @brief Represents a delay effect that applies a delay to the audio stream.
 * Inherits from the AbstractEffect class.
 */
class DelayEffect : public AbstractEffect {
public:
  /**
   * @brief Initializes a new instance of the DelayEffect class.
   */
  DelayEffect();

  /**
   * @brief Destroys the instance of the DelayEffect class.
   */
  ~DelayEffect() override;

  /**
   * @brief Applies the delay effect to the given audio buffer.
   * @param bufferToFill The audio buffer to apply the effect to.
   */
  void apply(const juce::AudioSourceChannelInfo &bufferToFill);

  /**
   * @brief Sets the rate of the delay effect.
   * @param rate The rate of the delay effect.
   */
  void setRate(float rate);

  /**
   * @brief Sets the delay of the effect.
   * @param delay The delay of the effect.
   */
  void setDelay(float delay);

  /**
   * @brief Compares the effect with another given effect.
   * @param effect The effect to compare with.
   * @return True if the effect is equal to the given effect, false otherwise.
   */
  bool operator==(const AbstractEffect *effect) override;

private:
  /**
   * @brief  The rate of the delay.
   */
  float rate;

  /**
   * @brief The delay of the effect.
   */
  float delay;
};
