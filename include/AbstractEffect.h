#pragma once
#include <JuceHeader.h>
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
     * @brief The name of the effect.
     */
    std::string effectName;

    /**
    * Tells if the effect is enabled or not.
    */
    bool* isEnabled = new bool(true);

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

    /**
     * @brief Serializes the effect to a JSON object.
     * @return JSON object containing serialized effect data.
     */
    [[nodiscard]] virtual var toJSON() const {
        const auto obj = new DynamicObject();
        obj->setProperty("id", id);
        obj->setProperty("author", var(author));
        obj->setProperty("description", var(description));
        obj->setProperty("version", var(version));
        obj->setProperty("type", getEffectType());
        return obj;
    }

    /**
     * @brief Deserializes the effect from a JSON object.
     * @param json JSON object containing serialized effect data.
     */
    virtual void fromJSON(const var &json) {
        if (const auto *obj = json.getDynamicObject()) {
            id = obj->getProperty("id");
            author = obj->getProperty("author").toString().toStdString();
            description = obj->getProperty("description").toString().toStdString();
            version = obj->getProperty("version").toString().toStdString();
        }
    }

    /**
       * @brief Gets the type name of the effect for serialization purposes.
       * @return A string representing the effect type.
       */
    [[nodiscard]] virtual String getEffectType() const = 0;

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

protected:
    /**
     * The sample rate of the audio stream.
     */
    double sampleRate = 44100.0f;
};