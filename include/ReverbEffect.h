#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"

class ReverbEffect  : public AbstractEffect
{
public:
    ReverbEffect();
    ~ReverbEffect() override;

    void prepare(const juce::dsp::ProcessSpec& spec);

    void reset() noexcept;

    void apply(const juce::AudioSourceChannelInfo& bufferToFill) override;

    bool operator== (const AbstractEffect* other) override;

    [[nodiscard]] String getEffectType() const override { return "ReverbEffect"; }


    [[nodiscard]] var toJSON() const override {
        auto obj = AbstractEffect::toJSON();
        return obj;
    }

    /**
     * @brief Deserializes the delay effect from a JSON object.
     * @param json JSON object containing serialized effect data.
     */
    void fromJSON(const var &json) override {
        AbstractEffect::fromJSON(json);
    }

private:
    juce::dsp::ProcessorChain<juce::dsp::Reverb> processorChain;
};
