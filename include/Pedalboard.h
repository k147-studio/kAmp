#pragma once

#include "AbstractEffect.h"
#include <juce_audio_utils/juce_audio_utils.h>

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
    Pedalboard(const std::vector<AbstractEffect*> &effects);

    /**
     * @brief Destroys the instance of the Pedalboard class.
     */
    ~Pedalboard() override;

    /**
     * @brief Applies all the effects in the pedalboard to the given audio buffer.
     * @param bufferToFill The audio buffer to apply the effects to.
     */
    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override;

    /**
     * @brief Compares the pedalboard with the given effect.
     * @param effect The effect to compare with.
     * @return True if the pedalboard is equal to the given effect, false otherwise.
     */
    bool operator==(const AbstractEffect* effect) override;

    /**
     * @brief Adds an effect at the end of the pedalboard.
     * @param effect The effect to add to the pedalboard.
     */
    void append(AbstractEffect* effect);

    /**
     * @brief Inserts an effect at the given index in the pedalboard.
     * @param effect The effect to insert into the pedalboard.
     * @param index The index where to insert the effect.
     */
    void insert(AbstractEffect* effect, int index);

    /**
     * @brief Removes the given effect from the pedalboard.
     * @param effect The effect to remove from the pedalboard.
     */
    void remove(const AbstractEffect* effect);

    /**
     * @brief Gets the collection of effects contained in the pedalboard.
     * @return The collection of effects contained in the pedalboard.
     */
    std::vector<AbstractEffect*> getEffects();

  private:
    /**
     * @brief The collection of effects contained in the pedalboard.
     */
    std::vector<AbstractEffect*> effects;
};