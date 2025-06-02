#include "DistortionEffect.h"
#include <cmath>

float gDrive = 1.0f;
bool gTurbo = false;

DistortionEffect::DistortionEffect() {
    effectName = "Distortion";
    updateWaveshaper();
    updateTone();
    processorChain.get<3>().setGainLinear(level);
}

DistortionEffect::~DistortionEffect() = default;

void DistortionEffect::prepare(const juce::dsp::ProcessSpec& spec) {
    processorChain.prepare(spec);
    // High-pass à 120 Hz
    *processorChain.get<0>().coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate, 120.0f);
    updateTone();
}

void DistortionEffect::reset() noexcept {
    processorChain.reset();
}

void DistortionEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill) {
    if (bufferToFill.buffer == nullptr) return;
    juce::dsp::AudioBlock<float> block(*bufferToFill.buffer, (size_t) bufferToFill.startSample);
    const int numChannels = block.getNumChannels();
    // auto subBlock = block.getSubBlock(0, (size_t) bufferToFill.numSamples);
    // juce::dsp::ProcessContextReplacing<float> context(subBlock);
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto channelBlock = block.getSingleChannelBlock((size_t)channel);
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        processorChain.process(context);
    }
}

// --- Paramètres ---

void DistortionEffect::setLevel(float value) {
    level = juce::jlimit(0.0f, 1.0f, value);
    processorChain.get<3>().setGainLinear(level);
}
void DistortionEffect::setTone(float value) {
    tone = juce::jlimit(0.0f, 1.0f, value);
    updateTone();
}
void DistortionEffect::setDist(float value) {
    dist = juce::jlimit(0.0f, 10.0f, value);
    updateWaveshaper();
}
void DistortionEffect::setTurbo(bool enabled) {
    turbo = enabled;
    updateWaveshaper();
    updateTone();
}

float DistortionEffect::getLevel() const { return level; }
float DistortionEffect::getTone() const { return tone; }
float DistortionEffect::getDist() const { return dist; }
bool DistortionEffect::isTurbo() const { return turbo; }

// --- DSP interne ---

void DistortionEffect::updateTone() {
    // Tone = low-pass variable, Turbo = plus d'aigus
    float freq = 2000.0f + tone * (turbo ? 8000.0f : 4000.0f); // 2kHz à 10kHz (Turbo) ou 2kHz à 6kHz
    *processorChain.get<2>().coefficients = *juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, freq);
}

float DistortionEffect::waveshaperFunc(float x) {
    // Utilise les membres statiques pour le drive/turbo
    // (Attention, non thread-safe, mais simple pour un test)
    extern float gDrive;
    extern bool gTurbo;
    if (gTurbo)
        return std::tanh(gDrive * x) * 1.2f;
    else
        return std::tanh(gDrive * x);
}

void DistortionEffect::updateWaveshaper() {
    float drive = 1.0f + dist * (turbo ?  100.0f : 50.0f); // Turbo = plus de gain
    gDrive = drive;
    gTurbo = turbo;
    processorChain.get<1>().functionToUse = &DistortionEffect::waveshaperFunc;
}