#include "AutoWahEffect.h"

#include <cmath>

AutoWahEffect::AutoWahEffect()
{
    effectName = "Auto-Wah";
    filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    envelope.setLevelCalculationType(juce::dsp::BallisticsFilterLevelCalculationType::peak);
    envelope.setAttackTime(5.0f);
    envelope.setReleaseTime(100.0f);
}

void AutoWahEffect::syncParameters()
{
    const float res = resonance.load(std::memory_order_relaxed);
    // Map 0..1 knob to a useful SVF resonance range.
    filter.setResonance(0.5f + res * 7.5f);
}

void AutoWahEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || bufferToFill.numSamples <= 0 || buffer->getNumChannels() == 0)
        return;

    syncParameters();

    const float sens = sensitivity.load(std::memory_order_relaxed);
    const float rangeValue = range.load(std::memory_order_relaxed);
    const float mixValue = mix.load(std::memory_order_relaxed);
    const float dryGain = 1.0f - mixValue;
    const float inputGain = juce::jmap(sens, 0.0f, 1.0f, 1.0f, 25.0f);
    const float maxSweepHz = minCutoffHz + rangeValue * (maxCutoffHz - minCutoffHz);

    const int numChannels = buffer->getNumChannels();
    const int startSample = bufferToFill.startSample;
    const int numSamples = bufferToFill.numSamples;

    for (int i = 0; i < numSamples; ++i)
    {
        float peak = 0.0f;
        for (int ch = 0; ch < numChannels; ++ch)
            peak = juce::jmax(peak, std::abs(buffer->getReadPointer(ch, startSample)[i]));

        // Shared mono envelope drives cutoff for all channels.
        const float env = juce::jlimit(0.0f, 1.0f, envelope.processSample(0, peak * inputGain));
        const float cutoff = juce::jmap(env, 0.0f, 1.0f, minCutoffHz, maxSweepHz);
        filter.setCutoffFrequency(cutoff);

        for (int ch = 0; ch < numChannels; ++ch)
        {
            float* sample = &buffer->getWritePointer(ch, startSample)[i];
            const float dry = *sample;
            const float wet = filter.processSample(ch, dry);
            *sample = dry * dryGain + wet * mixValue;
        }
    }
}

void AutoWahEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    envelope.prepare(spec);
    filter.prepare(spec);
    filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    filter.setCutoffFrequency(minCutoffHz);
    syncParameters();
}

void AutoWahEffect::reset()
{
    envelope.reset();
    filter.reset();
}

bool AutoWahEffect::operator==(const AbstractEffect* effect)
{
    return this == effect;
}

float AutoWahEffect::getSensitivity() const { return sensitivity.load(std::memory_order_relaxed); }
float AutoWahEffect::getRange() const { return range.load(std::memory_order_relaxed); }
float AutoWahEffect::getResonance() const { return resonance.load(std::memory_order_relaxed); }
float AutoWahEffect::getMix() const { return mix.load(std::memory_order_relaxed); }

void AutoWahEffect::setSensitivity(float value)
{
    sensitivity.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void AutoWahEffect::setRange(float value)
{
    range.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void AutoWahEffect::setResonance(float value)
{
    resonance.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void AutoWahEffect::setMix(float value)
{
    mix.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

juce::var AutoWahEffect::toJSON() const
{
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject())
    {
        dynamicObj->setProperty("sensitivity", getSensitivity());
        dynamicObj->setProperty("range", getRange());
        dynamicObj->setProperty("resonance", getResonance());
        dynamicObj->setProperty("mix", getMix());
    }
    return obj;
}

void AutoWahEffect::fromJSON(const juce::var& json)
{
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject())
    {
        if (obj->hasProperty("sensitivity"))
            setSensitivity(static_cast<float>(obj->getProperty("sensitivity")));
        if (obj->hasProperty("range"))
            setRange(static_cast<float>(obj->getProperty("range")));
        if (obj->hasProperty("resonance"))
            setResonance(static_cast<float>(obj->getProperty("resonance")));
        if (obj->hasProperty("mix"))
            setMix(static_cast<float>(obj->getProperty("mix")));
    }
}
