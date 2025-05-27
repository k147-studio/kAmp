#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"


/**
 * @brief Represents a distortion effect that applies non-linear clipping to the audio stream.
 * Inherits from the AbstractEffect class.
 */
class DistortionEffect : public AbstractEffect {
public:

    /**
     * @brief Initializes a new instance of the DistortionEffect class.
     */
    DistortionEffect();

    /**
     * @brief Destroys the instance of the DistortionEffect class.
     */
    ~DistortionEffect() override;

    /**
     * @brief Applies the distortion effect to the given audio buffer.
     * @param bufferToFill The audio buffer to apply the effect to.
     */
    void apply(const AudioSourceChannelInfo &bufferToFill) override;

    /**
     * @brief Sets the range amount for the distortion effect.
     * @param driveValue The drive (gain) amount before clipping.
     */
    void setRange(float rangeValue);

    static float clipWithCurrentRange(float x);



    void reset() noexcept;

    /**
     * @brief Compares the effect with another given effect.
     * @param effect The effect to compare with.
     * @return True if the effect is equal to the given effect, false otherwise.
     */
    bool operator==(const AbstractEffect *effect) override;


    void prepare(const juce::dsp::ProcessSpec& spec);

    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept;

    float getRange() const;


    /**
   * @brief Gets the type name of the effect for serialization purposes.
   * @return A string representing the effect type.
   */
    [[nodiscard]] String getEffectType() const override { return "DistortionEffect"; }

    /**
     * @brief Serializes the delay effect to a JSON object.
     * @return JSON object containing serialized effect data.
     */
    [[nodiscard]] var toJSON() const override {
        auto obj = AbstractEffect::toJSON();
        if (auto *dynamicObj = obj.getDynamicObject()) {
            dynamicObj->setProperty("range", currentRange);
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
            currentRange = static_cast<float>(obj->getProperty("range"));
        }
    }

private:
    static float currentRange;


    enum {
        waveshaperIndex // [2]
    };
    juce::dsp::ProcessorChain<juce::dsp::WaveShaper<float>> processorChain;
};
