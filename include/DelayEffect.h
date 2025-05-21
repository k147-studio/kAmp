#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"

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
  void apply(const AudioSourceChannelInfo &bufferToFill) override;

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

  /**
   * @brief Gets the type name of the effect for serialization purposes.
   * @return A string representing the effect type.
   */
  [[nodiscard]] String getEffectType() const override { return "DelayEffect"; }

  /**
   * @brief Serializes the delay effect to a JSON object.
   * @return JSON object containing serialized effect data.
   */
  [[nodiscard]] var toJSON() const override {
    auto obj = AbstractEffect::toJSON();
    if (auto *dynamicObj = obj.getDynamicObject()) {
      dynamicObj->setProperty("rate", rate);
      dynamicObj->setProperty("delay", delay);
    }
    return obj;
  }

  /**
   * @brief Deserializes the delay effect from a JSON object.
   * @param json JSON object containing serialized effect data.
   */
  void fromJSON(const var &json) override {
    AbstractEffect::fromJSON(json);

    if (const auto *obj = json.getDynamicObject()) {
      rate = static_cast<float>(obj->getProperty("rate"));
      delay = static_cast<float>(obj->getProperty("delay"));
    }
  }

private:
  /**
   * @brief  The rate of the delay.
   */
  float rate;

  /**
   * @brief The delay of the effect.
   */
  float delay;

  std::vector<float> circularBuffer;
  int writePosition = 0;
};
