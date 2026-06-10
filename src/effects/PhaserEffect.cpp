#include "PhaserEffect.h"

PhaserEffect::PhaserEffect()
{
    effectName = "Phaser";
}

void PhaserEffect::syncParameters()
{
    phaser.setRate(rate.load(std::memory_order_relaxed));
    phaser.setDepth(depth.load(std::memory_order_relaxed));
    phaser.setCentreFrequency(centreFrequency.load(std::memory_order_relaxed));
    phaser.setFeedback(feedback.load(std::memory_order_relaxed));
    phaser.setMix(mix.load(std::memory_order_relaxed));
}

void PhaserEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || buffer->getNumSamples() == 0 || buffer->getNumChannels() == 0)
        return;

    syncParameters();

    juce::dsp::AudioBlock<float> block(*buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    phaser.process(context);
}

void PhaserEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    phaser.prepare(spec);
    syncParameters();
}

void PhaserEffect::reset()
{
    phaser.reset();
}

bool PhaserEffect::operator==(const AbstractEffect* effect)
{
    return this == effect;
}

float PhaserEffect::getRate() const { return rate.load(std::memory_order_relaxed); }
float PhaserEffect::getDepth() const { return depth.load(std::memory_order_relaxed); }
float PhaserEffect::getCentreFrequency() const { return centreFrequency.load(std::memory_order_relaxed); }
float PhaserEffect::getFeedback() const { return feedback.load(std::memory_order_relaxed); }
float PhaserEffect::getMix() const { return mix.load(std::memory_order_relaxed); }

void PhaserEffect::setRate(float value)
{
    rate.store(juce::jlimit(0.0f, 99.0f, value), std::memory_order_relaxed);
}

void PhaserEffect::setDepth(float value)
{
    depth.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void PhaserEffect::setCentreFrequency(float value)
{
    centreFrequency.store(juce::jlimit(20.0f, 20000.0f, value), std::memory_order_relaxed);
}

void PhaserEffect::setFeedback(float value)
{
    feedback.store(juce::jlimit(-1.0f, 1.0f, value), std::memory_order_relaxed);
}

void PhaserEffect::setMix(float value)
{
    mix.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

juce::var PhaserEffect::toJSON() const
{
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject())
    {
        dynamicObj->setProperty("rate", getRate());
        dynamicObj->setProperty("depth", getDepth());
        dynamicObj->setProperty("centreFrequency", getCentreFrequency());
        dynamicObj->setProperty("feedback", getFeedback());
        dynamicObj->setProperty("mix", getMix());
    }
    return obj;
}

void PhaserEffect::fromJSON(const juce::var& json)
{
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject())
    {
        if (obj->hasProperty("rate"))
            setRate(static_cast<float>(obj->getProperty("rate")));
        if (obj->hasProperty("depth"))
            setDepth(static_cast<float>(obj->getProperty("depth")));
        if (obj->hasProperty("centreFrequency"))
            setCentreFrequency(static_cast<float>(obj->getProperty("centreFrequency")));
        if (obj->hasProperty("feedback"))
            setFeedback(static_cast<float>(obj->getProperty("feedback")));
        if (obj->hasProperty("mix"))
            setMix(static_cast<float>(obj->getProperty("mix")));
    }
}
