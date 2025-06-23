#pragma once

#include "AbstractEffect.h"

/**
 * @brief Represents a pedalboard that contains all the effects and apply them on the audio stream.
 * It inherits from the AbstractEffect class so we can include a pedalboard in another.
 */
class Pedalboard : public AbstractEffect {
public:
  /**
   * @brief Initializes a new instance of the Pedalboard class.
   */
  Pedalboard();

  /**
   * @brief Initializes a new instance of the Pedalboard class with the given effects.
   * @param effects The effects collection to initialize the pedalboard with.
   */
  explicit Pedalboard(const std::vector<AbstractEffect *> &effects);

  /**
   * @brief Destroys the instance of the Pedalboard class.
   */
  ~Pedalboard() override;

  /**
   * @brief Applies all the effects in the pedalboard to the given audio buffer.
   * @param bufferToFill The audio buffer to apply the effects to.
   */
  void apply(const AudioSourceChannelInfo &bufferToFill) override;

  /**
   * @brief Prepares the pedalboard for processing with the given process specification.
   * @param spec The process specification containing sample rate, block size, and number of channels.
   */
  void prepare(const juce::dsp::ProcessSpec &spec) override;

  /**
   * @brief Compares the pedalboard with the given effect.
   * @param effect The effect to compare with.
   * @return True if the pedalboard is equal to the given effect, false otherwise.
   */
  bool operator==(const AbstractEffect *effect) override;

  /**
   * @brief Adds an effect at the end of the pedalboard.
   * @param effect The effect to add to the pedalboard.
   */
  void append(AbstractEffect *effect);

  /**
   * @brief Adds all the effects from the given vector to the pedalboard.
   * @param effects The vector of effects to add to the pedalboard.
   */
  void appendAll(std::vector<AbstractEffect*> effects);

  /**
   * @brief Inserts an effect at the given index in the pedalboard.
   * @param effect The effect to insert into the pedalboard.
   * @param index The index where to insert the effect.
   */
  void insert(AbstractEffect *effect, int index);

  /**
   * @brief Removes the given effect from the pedalboard.
   * @param effect The effect to remove from the pedalboard.
   */
  void remove(const AbstractEffect *effect);

  /**
   * @brief Gets the collection of effects contained in the pedalboard.
   * @return The collection of effects contained in the pedalboard.
   */
  std::vector<AbstractEffect *>& getEffects();

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
    return obj;
  }

  /**
   * @brief Deserializes the delay effect from a JSON object.
   * @param json JSON object containing serialized effect data.
   */
  void fromJSON(const var &json) override {
    AbstractEffect::fromJSON(json);
  }

private:
  /**
   * @brief The collection of effects contained in the pedalboard.
   */
  std::vector<AbstractEffect *> effects;
};
