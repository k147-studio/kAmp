#include "TremoloEffect.h"

#include <cmath>

TremoloEffect::TremoloEffect()
{
    effectName = "Tremolo";
    lfo.initialise([](float x) { return std::sin(x); }, 128);
}

void TremoloEffect::syncParameters()
{
    lfo.setFrequency(rate.load(std::memory_order_relaxed));
}

void TremoloEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || bufferToFill.numSamples <= 0 || buffer->getNumChannels() == 0)
        return;

    syncParameters();

    const float depthValue = depth.load(std::memory_order_relaxed);
    const int numChannels = buffer->getNumChannels();
    const int startSample = bufferToFill.startSample;
    const int numSamples = bufferToFill.numSamples;

    for (int i = 0; i < numSamples; ++i)
    {
        // Advance LFO once per frame; same gain on all channels.
        const float lfoValue = lfo.processSample(0.0f); // -1..1
        const float gain = 1.0f - depthValue * (0.5f * (1.0f - lfoValue));

        for (int ch = 0; ch < numChannels; ++ch)
            buffer->getWritePointer(ch, startSample)[i] *= gain;
    }
}

void TremoloEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    lfo.prepare(spec);
    lfo.setFrequency(rate.load(std::memory_order_relaxed), true);
}

void TremoloEffect::reset()
{
    lfo.reset();
}

bool TremoloEffect::operator==(const AbstractEffect* effect)
{
    return this == effect;
}

float TremoloEffect::getRate() const { return rate.load(std::memory_order_relaxed); }
float TremoloEffect::getDepth() const { return depth.load(std::memory_order_relaxed); }

void TremoloEffect::setRate(float value)
{
    rate.store(juce::jlimit(0.1f, 20.0f, value), std::memory_order_relaxed);
}

void TremoloEffect::setDepth(float value)
{
    depth.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

juce::var TremoloEffect::toJSON() const
{
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject())
    {
        dynamicObj->setProperty("rate", getRate());
        dynamicObj->setProperty("depth", getDepth());
    }
    return obj;
}

void TremoloEffect::fromJSON(const juce::var& json)
{
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject())
    {
        if (obj->hasProperty("rate"))
            setRate(static_cast<float>(obj->getProperty("rate")));
        if (obj->hasProperty("depth"))
            setDepth(static_cast<float>(obj->getProperty("depth")));
    }
}
