#include "ReverbEffect.h"

ReverbEffect::ReverbEffect()
{
    effectName = "Reverb";
}

ReverbEffect::~ReverbEffect() = default;

void ReverbEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    processorChain.prepare(spec);

    juce::dsp::Reverb::Parameters p;
    p.roomSize   = 0.5f;
    p.damping    = 0.5f;
    p.wetLevel   = 0.33f;
    p.dryLevel   = 0.4f;
    p.width      = 1.0f;
    p.freezeMode = 0.0f;

    processorChain.get<0>().setParameters(p);
}

void ReverbEffect::reset() noexcept
{
    processorChain.reset();
}

void ReverbEffect::apply(const juce::AudioSourceChannelInfo& info)
{
    auto* buffer = info.buffer;
    if (! buffer)
        return;

    const int start      = info.startSample;
    const int numSamples = info.numSamples;
    const int numChans   = buffer->getNumChannels();

    if (start < 0 || numSamples <= 0)
        return;
    if (start + numSamples > buffer->getNumSamples())
        return;

    if (numChans < 2)
        return;

    juce::dsp::AudioBlock<float> block(*buffer);
    auto subBlock = block.getSubBlock(static_cast<size_t>(start),
                                      static_cast<size_t>(numSamples));

    juce::dsp::ProcessContextReplacing<float> context(subBlock);
    processorChain.process(context);
}

bool ReverbEffect::operator== (const AbstractEffect* other)
{
    return dynamic_cast<const ReverbEffect*>(other) != nullptr;
}
