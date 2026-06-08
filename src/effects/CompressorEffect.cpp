#include "CompressorEffect.h"

CompressorEffect::CompressorEffect()
{
    effectName = "Compressor";
}

void CompressorEffect::syncParameters()
{
    auto& compressor = processorChain.get<compressorIndex>();
    compressor.setThreshold(threshold.load(std::memory_order_relaxed));
    compressor.setRatio(ratio.load(std::memory_order_relaxed));
    compressor.setAttack(attack.load(std::memory_order_relaxed));
    compressor.setRelease(release.load(std::memory_order_relaxed));

    processorChain.get<gainIndex>().setGainDecibels(level.load(std::memory_order_relaxed));
}

void CompressorEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || buffer->getNumSamples() == 0 || buffer->getNumChannels() == 0)
        return;

    syncParameters();

    juce::dsp::AudioBlock<float> block(*buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    processorChain.process(context);
}

void CompressorEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    processorChain.prepare(spec);
    syncParameters();
}

void CompressorEffect::reset()
{
    processorChain.reset();
}

bool CompressorEffect::operator==(const AbstractEffect* effect)
{
    return this == effect;
}

float CompressorEffect::getThreshold() const { return threshold.load(std::memory_order_relaxed); }
float CompressorEffect::getRatio() const { return ratio.load(std::memory_order_relaxed); }
float CompressorEffect::getAttack() const { return attack.load(std::memory_order_relaxed); }
float CompressorEffect::getRelease() const { return release.load(std::memory_order_relaxed); }
float CompressorEffect::getLevel() const { return level.load(std::memory_order_relaxed); }

void CompressorEffect::setThreshold(float value)
{
    threshold.store(juce::jlimit(-60.0f, 0.0f, value), std::memory_order_relaxed);
}

void CompressorEffect::setRatio(float value)
{
    ratio.store(juce::jlimit(1.0f, 20.0f, value), std::memory_order_relaxed);
}

void CompressorEffect::setAttack(float value)
{
    attack.store(juce::jlimit(0.1f, 100.0f, value), std::memory_order_relaxed);
}

void CompressorEffect::setRelease(float value)
{
    release.store(juce::jlimit(10.0f, 1000.0f, value), std::memory_order_relaxed);
}

void CompressorEffect::setLevel(float value)
{
    level.store(juce::jlimit(0.0f, 24.0f, value), std::memory_order_relaxed);
}

juce::var CompressorEffect::toJSON() const
{
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject())
    {
        dynamicObj->setProperty("threshold", getThreshold());
        dynamicObj->setProperty("ratio", getRatio());
        dynamicObj->setProperty("attack", getAttack());
        dynamicObj->setProperty("release", getRelease());
        dynamicObj->setProperty("level", getLevel());
    }
    return obj;
}

void CompressorEffect::fromJSON(const juce::var& json)
{
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject())
    {
        if (obj->hasProperty("threshold"))
            setThreshold(static_cast<float>(obj->getProperty("threshold")));
        if (obj->hasProperty("ratio"))
            setRatio(static_cast<float>(obj->getProperty("ratio")));
        if (obj->hasProperty("attack"))
            setAttack(static_cast<float>(obj->getProperty("attack")));
        if (obj->hasProperty("release"))
            setRelease(static_cast<float>(obj->getProperty("release")));
        if (obj->hasProperty("level"))
            setLevel(static_cast<float>(obj->getProperty("level")));
    }
}
