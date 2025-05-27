#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"
#include <juce_dsp/juce_dsp.h>


class EqualizerEffect : public AbstractEffect {
public:
    EqualizerEffect();
    ~EqualizerEffect() override = default;

    void apply(const AudioSourceChannelInfo &bufferToFill) override;
    void setGain(int bandIndex, float gain);
    float getGain(int bandIndex) const;
    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] String getEffectType() const override { return "EqualizerEffect"; }

    [[nodiscard]] var toJSON() const override;
    void fromJSON(const var &json) override;

private:
    static constexpr int numBands = 10;
    float bandGains[numBands]; // Gain en dB pour chaque bande
    std::vector<dsp::IIR::Filter<float>> filters;

    void updateFilters();
};
