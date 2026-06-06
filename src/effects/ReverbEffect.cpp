#include "ReverbEffect.h"

ReverbEffect::ReverbEffect()
{
    effectName = "Reverb";
}

void ReverbEffect::syncParameters()
{
    juce::Reverb::Parameters params;
    params.roomSize = size.load(std::memory_order_relaxed);
    params.damping = damp.load(std::memory_order_relaxed);
    params.width = width.load(std::memory_order_relaxed);

    const float mixValue = mix.load(std::memory_order_relaxed);
    params.wetLevel = mixValue;
    params.dryLevel = 1.0f - mixValue;
    params.freezeMode = 0.0f;

    reverb.setParameters(params);
}

void ReverbEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || buffer->getNumSamples() == 0 || buffer->getNumChannels() == 0)
        return;

    syncParameters();

    juce::dsp::AudioBlock<float> block(*buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    reverb.process(context);
}

void ReverbEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    reverb.prepare(spec);
    syncParameters();
}

void ReverbEffect::reset()
{
    reverb.reset();
}

bool ReverbEffect::operator==(const AbstractEffect* effect)
{
    return this == effect;
}

float ReverbEffect::getMix() const { return mix.load(std::memory_order_relaxed); }
float ReverbEffect::getSize() const { return size.load(std::memory_order_relaxed); }
float ReverbEffect::getDamp() const { return damp.load(std::memory_order_relaxed); }
float ReverbEffect::getWidth() const { return width.load(std::memory_order_relaxed); }

void ReverbEffect::setMix(float value)
{
    mix.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void ReverbEffect::setSize(float value)
{
    size.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void ReverbEffect::setDamp(float value)
{
    damp.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void ReverbEffect::setWidth(float value)
{
    width.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

juce::var ReverbEffect::toJSON() const
{
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject())
    {
        dynamicObj->setProperty("mix", getMix());
        dynamicObj->setProperty("roomSize", getSize());
        dynamicObj->setProperty("damping", getDamp());
        dynamicObj->setProperty("width", getWidth());
    }
    return obj;
}

void ReverbEffect::fromJSON(const juce::var& json)
{
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject())
    {
        if (obj->hasProperty("mix"))
            setMix(static_cast<float>(obj->getProperty("mix")));
        if (obj->hasProperty("roomSize"))
            setSize(static_cast<float>(obj->getProperty("roomSize")));
        if (obj->hasProperty("damping"))
            setDamp(static_cast<float>(obj->getProperty("damping")));
        if (obj->hasProperty("width"))
            setWidth(static_cast<float>(obj->getProperty("width")));
    }
}
