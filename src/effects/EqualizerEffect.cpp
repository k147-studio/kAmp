#include "EqualizerEffect.h"
#include <juce_dsp/juce_dsp.h>

EqualizerEffect::EqualizerEffect() {
    effectName = "Equalizer";
    filters.resize(numBands);
    for (int i = 0; i < numBands; ++i) bandGains[i] = 0.0f;
    updateFilters();
}

void EqualizerEffect::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    juce::dsp::AudioBlock<float> block(*bufferToFill.buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    for (int i = 0; i < numBands; ++i) {
        filters[i].process(context);
    }
}

void EqualizerEffect::setGain(int bandIndex, float gain) {
    if (bandIndex >= 0 && bandIndex < numBands) {
        bandGains[bandIndex] = gain;
        updateFilters();
    }
}

float EqualizerEffect::getGain(int bandIndex) const {
    return (bandIndex >= 0 && bandIndex < numBands) ? bandGains[bandIndex] : 0.0f;
}

void EqualizerEffect::updateFilters() {
    // Fréquences fixes typiques d'un égaliseur 10 bandes
    const float freqs[10] = {31, 62, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    constexpr float sampleRate = 44100.0f;

    for (int i = 0; i < numBands; ++i) {
        filters[i].reset();
        auto coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(
            sampleRate, freqs[i], 1.0f, juce::Decibels::decibelsToGain(bandGains[i])
        );
        filters[i].coefficients = coeffs;
    }
}

bool EqualizerEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}

juce::var EqualizerEffect::toJSON() const {
    auto obj = AbstractEffect::toJSON();
    if (auto *dynamicObj = obj.getDynamicObject()) {
        juce::Array<juce::var> gains;
        for (float g : bandGains) gains.add(g);
        dynamicObj->setProperty("bandGains", gains);
    }
    return obj;
}

void EqualizerEffect::fromJSON(const juce::var &json) {
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject()) {
        const auto& gains = obj->getProperty("bandGains");
        if (auto* arr = gains.getArray()) {
            for (int i = 0; i < juce::jmin((int)arr->size(), numBands); ++i) {
                bandGains[i] = static_cast<float>((*arr)[i]);
            }
            updateFilters();
        }
    }
}
