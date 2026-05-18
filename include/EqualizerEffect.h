#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"
#include <juce_dsp/juce_dsp.h>
#include <array>
#include <atomic>


class EqualizerEffect : public AbstractEffect {
public:
    EqualizerEffect();
    ~EqualizerEffect() override = default;

    void apply(const AudioSourceChannelInfo &bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;
    void setGain(int bandIndex, float gain);
    float getGain(int bandIndex) const;
    bool operator==(const AbstractEffect* effect) override;

    [[nodiscard]] String getEffectType() const override { return "EqualizerEffect"; }

    [[nodiscard]] var toJSON() const override;
    void fromJSON(const var &json) override;

private:
    static constexpr int numBands = 10;

    void syncFilters();

    std::array<std::atomic<float>, numBands> bandGains {};
    std::atomic<bool> filtersNeedUpdate { true };
    std::vector<dsp::IIR::Filter<float>> filters;
    double sampleRate = 44100.0;
};
