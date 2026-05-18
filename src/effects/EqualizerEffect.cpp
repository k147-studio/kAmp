#include "EqualizerEffect.h"
#include <juce_dsp/juce_dsp.h>

EqualizerEffect::EqualizerEffect() {
    effectName = "Equalizer";
    filters.resize(numBands);
    for (auto& gain : bandGains)
        gain.store(0.0f, std::memory_order_relaxed);
    filtersNeedUpdate.store(true, std::memory_order_relaxed);
}

void EqualizerEffect::prepare(const juce::dsp::ProcessSpec& spec) {
    sampleRate = spec.sampleRate > 0.0 ? spec.sampleRate : 44100.0;
    for (auto& filter : filters)
        filter.prepare(spec);
    filtersNeedUpdate.store(true, std::memory_order_relaxed);
    syncFilters();
}

void EqualizerEffect::reset() {
    for (auto& filter : filters)
        filter.reset();
}

void EqualizerEffect::syncFilters() {
    if (!filtersNeedUpdate.exchange(false, std::memory_order_acq_rel))
        return;

    const float freqs[10] = {31, 62, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    const double nyquist = sampleRate * 0.5;

    for (int i = 0; i < numBands; ++i) {
        const float freq = static_cast<float>(juce::jmin(static_cast<double>(freqs[i]), nyquist * 0.99));
        const float gainDb = bandGains[static_cast<size_t>(i)].load(std::memory_order_relaxed);
        auto coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(
            sampleRate, freq, 1.0f, juce::Decibels::decibelsToGain(gainDb)
        );
        filters[static_cast<size_t>(i)].coefficients = coeffs;
    }
}

void EqualizerEffect::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    syncFilters();

    auto* buffer = bufferToFill.buffer;
    const int numChannels = buffer->getNumChannels();

    juce::dsp::AudioBlock<float> block(*buffer);

    for (int channel = 0; channel < numChannels; ++channel) {
        auto channelBlock = block.getSingleChannelBlock((size_t)channel);
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);

        for (int i = 0; i < numBands; ++i) {
            filters[static_cast<size_t>(i)].process(context);
        }
    }
}

void EqualizerEffect::setGain(int bandIndex, float gain) {
    if (bandIndex >= 0 && bandIndex < numBands) {
        bandGains[static_cast<size_t>(bandIndex)].store(gain, std::memory_order_relaxed);
        filtersNeedUpdate.store(true, std::memory_order_release);
    }
}

float EqualizerEffect::getGain(int bandIndex) const {
    return (bandIndex >= 0 && bandIndex < numBands)
               ? bandGains[static_cast<size_t>(bandIndex)].load(std::memory_order_relaxed)
               : 0.0f;
}

bool EqualizerEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}

juce::var EqualizerEffect::toJSON() const {
    auto obj = AbstractEffect::toJSON();
    if (auto *dynamicObj = obj.getDynamicObject()) {
        juce::Array<juce::var> gains;
        for (const auto& g : bandGains)
            gains.add(g.load(std::memory_order_relaxed));
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
                bandGains[static_cast<size_t>(i)].store(static_cast<float>((*arr)[i]), std::memory_order_relaxed);
            }
            filtersNeedUpdate.store(true, std::memory_order_release);
        }
    }
}
