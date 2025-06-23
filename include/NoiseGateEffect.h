#pragma once
#include "AbstractEffect.h"

/**
 * @brief Represents a noise gate effect that applies a noise gate to the audio stream.
 * Inherits from the AbstractEffect class.
 */
class NoiseGateEffect: public AbstractEffect
{
public:
    /**
     * @brief Initializes a new instance of the NoiseGateEffect class.
     */
    NoiseGateEffect();

    /**
     * @brief Destroys the instance of the NoiseGateEffect class.
     */
    ~NoiseGateEffect() override;

    /**
     * @brief Applies the noise gate effect to the given audio buffer.
     * @param bufferToFill The audio buffer to apply the effect to.
     */
    void apply(const AudioSourceChannelInfo &bufferToFill) override;

    /**
     * @brief Prepares the noise gate effect for processing with the given process specification.
     * @param spec The process specification containing sample rate, block size, and number of channels.
     */
    void prepare(const juce::dsp::ProcessSpec& spec) override;

    /**
     * @brief Sets the threshold of the noise gate effect.
     * @param threshold The threshold of the noise gate effect.
     */
    void setThreshold(float threshold);

    /**
     * @brief Sets the attack time of the noise gate effect.
     * @param attack The attack time of the noise gate effect.
     */
    void setAttack(float attack);

    /**
     * @brief Sets the release time of the noise gate effect.
     * @param release The release time of the noise gate effect.
     */
    void setRelease(float release);

    /**
     * @brief Compares the effect with another given effect.
     * @param effect The effect to compare with.
     * @return True if the effect is equal to the given effect, false otherwise.
     */
    bool operator==(const AbstractEffect* effect) override;

    /**
   * @brief Gets the type name of the effect for serialization purposes.
   * @return A string representing the effect type.
   */
    [[nodiscard]] String getEffectType() const override { return "NoiseGateEffect"; }

    /**
   * @brief Serializes the delay effect to a JSON object.
   * @return JSON object containing serialized effect data.
   */
    [[nodiscard]] var toJSON() const override {
        auto obj = AbstractEffect::toJSON();
        if (auto *dynamicObj = obj.getDynamicObject()) {
            dynamicObj->setProperty("threshold", threshold);
            dynamicObj->setProperty("attack", attack);
            dynamicObj->setProperty("release", release);
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
            threshold = static_cast<float>(obj->getProperty("threshold"));
            attack = static_cast<float>(obj->getProperty("attack"));
            release = static_cast<float>(obj->getProperty("release"));
        }
    }
private:
    /**
     * @brief The threshold of the noise gate effect.
     */
    float threshold;

    /**
     * @brief The attack time of the noise gate effect.
     */
    float attack;

    /**
     * @brief The release time of the noise gate effect.
     */
    float release;
};
