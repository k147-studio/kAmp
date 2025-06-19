#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>
#include "AbstractEffect.h"

class DistortionEffect : public AbstractEffect {
public:
    DistortionEffect();
    ~DistortionEffect() override;

    void apply(const AudioSourceChannelInfo &bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset() noexcept;

    // Paramètres Boss DS-2
    void setLevel(float value); // 0.0 à 1.0
    void setTone(float value);  // 0.0 à 1.0
    void setDist(float value);  // 0.0 à 1.0
    void setTurbo(bool enabled);

    float getLevel() const;
    float getTone() const;
    float getDist() const;
    bool isTurbo() const;

    // (Sérialisation, etc.)
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
            dynamicObj->setProperty("level", level);
            dynamicObj->setProperty("tone", tone);
            dynamicObj->setProperty("dist", dist);
            dynamicObj->setProperty("turbo", turbo);
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
            if (obj->hasProperty("level")) level = static_cast<float>(obj->getProperty("level"));
            if (obj->hasProperty("tone"))  tone  = static_cast<float>(obj->getProperty("tone"));
            if (obj->hasProperty("dist"))  dist  = static_cast<float>(obj->getProperty("dist"));
            if (obj->hasProperty("turbo")) turbo = static_cast<bool>(obj->getProperty("turbo"));
            updateWaveshaper();
            updateTone();
            processorChain.get<3>().setGainLinear(level);
        }
    }

    bool operator==(const AbstractEffect* other);

private:
    float level = 1.0f;
    float tone = 0.5f;
    float dist = 0.5f;
    bool turbo = false;
    float currentDrive = 1.0f;
    bool currentTurbo = false;

    juce::dsp::ProcessorChain<
        juce::dsp::IIR::Filter<float>, // High-pass
        juce::dsp::WaveShaper<float>,  // Distorsion
        juce::dsp::IIR::Filter<float>, // Tone (low-pass)
        juce::dsp::Gain<float>         // Level
    > processorChain;

    void updateTone();

    static float waveshaperFunc(float x);
    void updateWaveshaper();
};