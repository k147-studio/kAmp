#pragma once
#include "AbstractEffect.h"
#include <atomic>

/**
 * @brief Represents a noise gate effect that applies a noise gate to the audio stream.
 * Inherits from the AbstractEffect class.
 */
class NoiseGateEffect: public AbstractEffect
{
public:
    NoiseGateEffect();
    ~NoiseGateEffect() override;

    void apply(const AudioSourceChannelInfo &bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;

    void setThreshold(float threshold);
    void setAttack(float attack);
    void setRelease(float release);

    [[nodiscard]] float getThreshold() const noexcept;
    [[nodiscard]] float getAttack() const noexcept;
    [[nodiscard]] float getRelease() const noexcept;

    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] String getEffectType() const override { return "NoiseGateEffect"; }

    [[nodiscard]] var toJSON() const override {
        auto obj = AbstractEffect::toJSON();
        if (auto *dynamicObj = obj.getDynamicObject()) {
            dynamicObj->setProperty("threshold", getThreshold());
            dynamicObj->setProperty("attack", getAttack());
            dynamicObj->setProperty("release", getRelease());
        }
        return obj;
    }

    void fromJSON(const var &json) override {
        AbstractEffect::fromJSON(json);

        if (const auto *obj = json.getDynamicObject()) {
            setThreshold(static_cast<float>(obj->getProperty("threshold")));
            setAttack(static_cast<float>(obj->getProperty("attack")));
            setRelease(static_cast<float>(obj->getProperty("release")));
        }
    }
private:
    std::atomic<float> threshold { 0.5f };
    std::atomic<float> attack { 0.01f };
    std::atomic<float> release { 0.1f };

    double sampleRate = 44100.0;
};
