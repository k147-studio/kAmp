#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>
#include "AbstractEffect.h"
#include <atomic>
#include <cmath>

class DistortionEffect : public AbstractEffect {
public:
    DistortionEffect();
    ~DistortionEffect() override;

    void apply(const AudioSourceChannelInfo &bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() noexcept override;

    // Paramètres Boss DS-2
    void setLevel(float value); // 0.0 à 1.0
    void setTone(float value);  // 0.0 à 1.0
    void setDist(float value);  // 0.0 à 1.0
    void setTurbo(bool enabled);

    float getLevel() const;
    float getTone() const;
    float getDist() const;
    bool isTurbo() const;

    [[nodiscard]] String getEffectType() const override { return "DistortionEffect"; }

    [[nodiscard]] var toJSON() const override {
        auto obj = AbstractEffect::toJSON();
        if (auto *dynamicObj = obj.getDynamicObject()) {
            dynamicObj->setProperty("level", getLevel());
            dynamicObj->setProperty("tone", getTone());
            dynamicObj->setProperty("dist", getDist());
            dynamicObj->setProperty("turbo", isTurbo());
        }
        return obj;
    }

    void fromJSON(const var &json) override {
        AbstractEffect::fromJSON(json);
        if (const auto *obj = json.getDynamicObject()) {
            if (obj->hasProperty("level")) setLevel(static_cast<float>(obj->getProperty("level")));
            if (obj->hasProperty("tone"))  setTone(static_cast<float>(obj->getProperty("tone")));
            if (obj->hasProperty("dist"))  setDist(static_cast<float>(obj->getProperty("dist")));
            if (obj->hasProperty("turbo")) setTurbo(static_cast<bool>(obj->getProperty("turbo")));
        }
    }

    bool operator==(const AbstractEffect* other) override
    {
        const auto* o = dynamic_cast<const DistortionEffect*>(other);
        return o != nullptr &&
               juce::approximatelyEqual(getLevel(), o->getLevel()) &&
               juce::approximatelyEqual(getTone(), o->getTone()) &&
               juce::approximatelyEqual(getDist(), o->getDist()) &&
               isTurbo() == o->isTurbo();
    }

private:
    struct DriveShaper
    {
        float* drive = nullptr;
        bool* turbo = nullptr;

        float operator()(float x) const noexcept
        {
            const float shaped = std::tanh((*drive) * x);
            return *turbo ? shaped * 1.2f : shaped;
        }
    };

    void syncParameters();
    void updateTone(float toneValue, bool turboEnabled);

    std::atomic<float> level { 1.0f };
    std::atomic<float> tone { 0.5f };
    std::atomic<float> dist { 0.5f };
    std::atomic<bool> turbo { false };

    // Audio-thread-only cached DSP state (written in syncParameters / apply)
    float audioDrive = 1.0f;
    bool audioTurbo = false;
    float audioLevel = 1.0f;
    float audioTone = 0.5f;
    double sampleRate = 44100.0;

    juce::dsp::ProcessorChain<
        juce::dsp::IIR::Filter<float>,              // High-pass
        juce::dsp::WaveShaper<float, DriveShaper>,  // Distortion
        juce::dsp::IIR::Filter<float>,              // Tone (low-pass)
        juce::dsp::Gain<float>                      // Level
    > processorChain;
};
