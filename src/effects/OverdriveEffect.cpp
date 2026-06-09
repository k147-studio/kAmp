#include "OverdriveEffect.h"

OverdriveEffect::OverdriveEffect()
{
    effectName = "Overdrive";
    processorChain.get<2>().functionToUse = SoftClipShaper { &audioDrive };
    syncParameters();
}

void OverdriveEffect::syncParameters()
{
    const float newDrive = drive.load(std::memory_order_relaxed);
    const float newTone = tone.load(std::memory_order_relaxed);
    const float newLevel = level.load(std::memory_order_relaxed);

    audioDrive = 1.0f + newDrive * 40.0f;

    if (!juce::approximatelyEqual(newTone, audioTone))
        updateTone(newTone);

    audioTone = newTone;
    processorChain.get<4>().setGainLinear(newLevel);
}

void OverdriveEffect::updateTone(float toneValue)
{
    const float freq = 500.0f + toneValue * 5500.0f;
    *processorChain.get<3>().state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, freq);
}

void OverdriveEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || buffer->getNumSamples() == 0 || buffer->getNumChannels() == 0)
        return;

    syncParameters();

    juce::dsp::AudioBlock<float> block(*buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    processorChain.process(context);
}

void OverdriveEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate > 0.0 ? spec.sampleRate : 44100.0;
    processorChain.prepare(spec);

    *processorChain.get<0>().state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 80.0f);
    *processorChain.get<1>().state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(
        sampleRate, 720.0f, 0.9f, juce::Decibels::decibelsToGain(6.0f));

    audioTone = -1.0f;
    syncParameters();
}

void OverdriveEffect::reset()
{
    processorChain.reset();
}

bool OverdriveEffect::operator==(const AbstractEffect* effect)
{
    return this == effect;
}

float OverdriveEffect::getDrive() const { return drive.load(std::memory_order_relaxed); }
float OverdriveEffect::getTone() const { return tone.load(std::memory_order_relaxed); }
float OverdriveEffect::getLevel() const { return level.load(std::memory_order_relaxed); }

void OverdriveEffect::setDrive(float value)
{
    drive.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void OverdriveEffect::setTone(float value)
{
    tone.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void OverdriveEffect::setLevel(float value)
{
    level.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

juce::var OverdriveEffect::toJSON() const
{
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject())
    {
        dynamicObj->setProperty("drive", getDrive());
        dynamicObj->setProperty("tone", getTone());
        dynamicObj->setProperty("level", getLevel());
    }
    return obj;
}

void OverdriveEffect::fromJSON(const juce::var& json)
{
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject())
    {
        if (obj->hasProperty("drive"))
            setDrive(static_cast<float>(obj->getProperty("drive")));
        if (obj->hasProperty("tone"))
            setTone(static_cast<float>(obj->getProperty("tone")));
        if (obj->hasProperty("level"))
            setLevel(static_cast<float>(obj->getProperty("level")));
    }
}
