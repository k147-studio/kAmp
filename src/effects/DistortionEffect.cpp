#include "DistortionEffect.h"

DistortionEffect::DistortionEffect() {
    effectName = "Distortion";
    processorChain.get<1>().functionToUse = DriveShaper { &audioDrive, &audioTurbo };
    syncParameters();
}

DistortionEffect::~DistortionEffect() = default;

void DistortionEffect::prepare(const juce::dsp::ProcessSpec& spec) {
    sampleRate = spec.sampleRate > 0.0 ? spec.sampleRate : 44100.0;
    processorChain.prepare(spec);
    *processorChain.get<0>().coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 120.0f);
    syncParameters();
}

void DistortionEffect::reset() noexcept {
    processorChain.reset();
}

void DistortionEffect::syncParameters() {
    const float newLevel = level.load(std::memory_order_relaxed);
    const float newTone = tone.load(std::memory_order_relaxed);
    const float newDist = dist.load(std::memory_order_relaxed);
    const bool newTurbo = turbo.load(std::memory_order_relaxed);

    audioDrive = 1.0f + newDist * (newTurbo ? 100.0f : 50.0f);

    if (!juce::approximatelyEqual(newTone, audioTone) || newTurbo != audioTurbo)
        updateTone(newTone, newTurbo);

    audioLevel = newLevel;
    audioTone = newTone;
    audioTurbo = newTurbo;
    processorChain.get<3>().setGainLinear(audioLevel);
}

void DistortionEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill) {
    if (bufferToFill.buffer == nullptr) return;

    syncParameters();

    juce::dsp::AudioBlock<float> block(*bufferToFill.buffer, (size_t) bufferToFill.startSample);
    const int numChannels = static_cast<int>(block.getNumChannels());
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto channelBlock = block.getSingleChannelBlock((size_t)channel);
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        processorChain.process(context);
    }
}

void DistortionEffect::setLevel(float value) {
    level.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void DistortionEffect::setTone(float value) {
    tone.store(juce::jlimit(0.0f, 1.0f, value), std::memory_order_relaxed);
}

void DistortionEffect::setDist(float value) {
    dist.store(juce::jlimit(0.0f, 10.0f, value), std::memory_order_relaxed);
}

void DistortionEffect::setTurbo(bool enabled) {
    turbo.store(enabled, std::memory_order_relaxed);
}

float DistortionEffect::getLevel() const { return level.load(std::memory_order_relaxed); }
float DistortionEffect::getTone() const { return tone.load(std::memory_order_relaxed); }
float DistortionEffect::getDist() const { return dist.load(std::memory_order_relaxed); }
bool DistortionEffect::isTurbo() const { return turbo.load(std::memory_order_relaxed); }

void DistortionEffect::updateTone(float toneValue, bool turboEnabled) {
    const float freq = 2000.0f + toneValue * (turboEnabled ? 8000.0f : 4000.0f);
    *processorChain.get<2>().coefficients = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, freq);
}
