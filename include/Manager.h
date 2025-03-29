#pragma once

#include "Pedalboard.h"

/**
 * @brief Manages the effects in currently used in the pedalboard.
 */
class Manager {
  public:
    Manager(AbstractEffect* pedalboard);

    /**
     * @brief Applies the effects from the pedalboard to the given audio buffer.
     * @param bufferToFill The audio buffer to apply the effects to.
     */
    void apply(const juce::AudioSourceChannelInfo &bufferToFill);

    /**
     * @brief Imports a pedalboard.
     */
    void import();

    /**
     * @brief Adds the given effect at the end of the pedalboard.
     * @param effect The effect to append in the pealboard.
     */
    void append(AbstractEffect* effect);

    /**
     * @brief Exports all the pedalboard.
     */
    void exportAll();

    /**
     * Exports a given list of effects from the pedalboard.
     */
    void exportSelection();

    /**
     * @brief Gets the pedalboard.
     * @return The pedalboard.
     */
    AbstractEffect* getPedalboard();
  private:
    /**
     * @brief The pedalboard that contains all the currently used effects.
     */
    AbstractEffect* pedalboard;
};