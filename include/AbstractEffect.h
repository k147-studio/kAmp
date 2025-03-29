#pragma once
#include "IEffect.h"
#include <string>

/**
 * @brief Abstract class that represents an effect by determining
 * the minimum caracteristics an effect should have.
 * Implements the IEffect interface.
 */
class AbstractEffect : public IEffect {
  public:
    /**
     * @brief Initializes a new instance of the AbstractEffect class.
     */
    AbstractEffect() = default;

    /**
     * @brief Destroys the instance of the AbstractEffect class.
     */
    ~AbstractEffect() override = default;

    /**
     * @brief Gets the id of the effect.
     * @return The id of the effect.
     */
    int getId();

    /**
     * @brief Gets the name of the author of the effect.
     * @return The name of the author of the effect.
     */
    std::string getAuthor();

    /**
     * @brief Gets the description of the effect.
     * @return The description of the effect.
     */
    std::string getDescription();

    /**
     * @brief Gets the version of the effect.
     * @return The version of the effect.
     */
    std::string getVersion();

    /**
     * @brief Compares the effect with another given effect.
     * @param effect The effect to compare with.
     * @return True if the effect is equal to the given effect, false otherwise.
     */
    virtual bool operator==(const AbstractEffect* effect) = 0;

    /**
     * @brief Applies the effect to the given audio buffer.
     * @param bufferToFill The audio buffer to apply the effect to.
     */
    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override = 0;

  private:
    /**
     * @brief The id of the effect.
     */
    int id;

    /**
     * @brief The name of the author of the effect.
     */
    std::string author;

    /**
     * @brief The description of the effect.
     */
    std::string description;

    /**
     * @brief The version of the effect.
     */
    std::string version;
};