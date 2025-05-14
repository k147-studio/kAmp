#pragma once

#include "Pedalboard.h"

/**
 * @brief Manages the effects in currently used in the pedalboard.
 */
class Manager {
public:
  explicit Manager(AbstractEffect *pedalboard);

  /**
   * @brief Applies the effects from the pedalboard to the given audio buffer.
   * @param bufferToFill The audio buffer to apply the effects to.
   */
  void apply(const juce::AudioSourceChannelInfo &bufferToFill) const;

  /**
   * @brief Imports a pedalboard.
   */
  void importF() const;

  /**
   * @brief Adds the given effect at the end of the pedalboard.
   * @param effect The effect to append in the pedalboard.
   */
  void append(AbstractEffect *effect) const;

  /**
   * @brief Exports all the pedalboard.
   */
  void exportAll() const;

  /**
   * Exports a given list of effects from the pedalboard.
   */
  void exportSelection() const;

  /**
   * @brief Gets the pedalboard.
   * @return The pedalboard.
   */
  [[nodiscard]]
  AbstractEffect *getPedalboard() const;

private:
  /**
   * @brief The pedalboard that contains all the currently used effects.
   */
  AbstractEffect *pedalboard;
};
