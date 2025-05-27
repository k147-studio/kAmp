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
     * @brief Sets the drive amount for the distortion effect.
     * @param driveValue The drive (gain) amount before clipping.
     */
    void setDrive(float driveValue);

    /**
     * @brief Sets the mix (dry/wet) of the distortion effect.
     * @param mixValue The mix between dry and wet signal (0.0 = dry, 1.0 = wet).
     */
    void setMix(float mixValue);

    /**
     * @brief Compares the effect with another given effect.
     * @param effect The effect to compare with.
     * @return True if the effect is equal to the given effect, false otherwise.
     */
    bool operator==(const AbstractEffect *effect) override;


    void prepare(const juce::dsp::ProcessSpec& spec);

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
            dynamicObj->setProperty("drive", drive);
            dynamicObj->setProperty("mix", mix);
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
            drive = static_cast<float>(obj->getProperty("drive"));
            mix = static_cast<float>(obj->getProperty("mix"));
        }
    }

private:
    /**
     * @brief The drive amount applied before clipping.
     */
    float drive;

    /**
     * @brief The dry/wet mix of the effect.
     */
    float mix;

    enum
    {
        waveshaperIndex
    };

    using ShaperType = juce::dsp::WaveShaper<float, std::function<float(float)>>;
    juce::dsp::ProcessorChain<ShaperType> processorChain;
};
