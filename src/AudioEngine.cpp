#include "AudioEngine.h"

#include <cmath>

AudioEngine::AudioEngine(std::unique_ptr<Pedalboard> pedalboardToOwn)
    : pedalboard(std::move(pedalboardToOwn))
{
    jassert(pedalboard != nullptr);
}

Pedalboard& AudioEngine::getPedalboard() noexcept
{
    return *pedalboard;
}

const Pedalboard& AudioEngine::getPedalboard() const noexcept
{
    return *pedalboard;
}

void AudioEngine::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    tuner = std::make_unique<ChromaticTuner>(fftOrder, sampleRate);
    smoothedFrequency = 0.0f;
    pedalboard->prepare(spec);
}

void AudioEngine::process(const AudioSourceChannelInfo& bufferToFill)
{
    if (bufferToFill.buffer == nullptr)
        return;

    if (tuningState.enabled.load(std::memory_order_relaxed))
        processTuner(bufferToFill);

    if (muted.load(std::memory_order_relaxed))
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    pedalboard->apply(bufferToFill);
}

void AudioEngine::reset()
{
    pedalboard->reset();
    smoothedFrequency = 0.0f;
    tuningState.hasSignal.store(false, std::memory_order_relaxed);
}

void AudioEngine::processTuner(const AudioSourceChannelInfo& bufferToFill)
{
    if (tuner == nullptr || bufferToFill.buffer->getNumChannels() == 0)
        return;

    juce::dsp::AudioBlock<float> audioBlock(*bufferToFill.buffer);
    if (audioBlock.getNumSamples() == 0)
        return;

    auto mono = audioBlock.getSingleChannelBlock(0);
    const auto frequency = tuner->getMainFrequencyFromAudioBlock(mono);

    if (!frequency.has_value())
    {
        tuningState.hasSignal.store(false, std::memory_order_relaxed);
        return;
    }

    const float newFreq = *frequency;
    if (smoothedFrequency == 0.0f)
        smoothedFrequency = newFreq;
    else
        smoothedFrequency = smoothingCoeff * newFreq + (1.0f - smoothingCoeff) * smoothedFrequency;

    publishTuning(smoothedFrequency);
}

void AudioEngine::publishTuning(float frequency)
{
    if (frequency < 20.0f)
    {
        tuningState.hasSignal.store(false, std::memory_order_relaxed);
        tuningState.frequency.store(0.0f, std::memory_order_relaxed);
        tuningState.cents.store(0.0f, std::memory_order_relaxed);
        tuningState.midiNote.store(-1, std::memory_order_relaxed);
        tuningState.isInTune.store(false, std::memory_order_relaxed);
        return;
    }

    const float midiFloat = 69.0f + 12.0f * std::log2(frequency / 440.0f);
    const int midiNote = static_cast<int>(std::round(midiFloat));
    const float exactFrequency = 440.0f * std::pow(2.0f, static_cast<float>(midiNote - 69) / 12.0f);
    const float deviation = 1200.0f * std::log2(frequency / exactFrequency);

    tuningState.hasSignal.store(true, std::memory_order_relaxed);
    tuningState.frequency.store(frequency, std::memory_order_relaxed);
    tuningState.cents.store(deviation, std::memory_order_relaxed);
    tuningState.midiNote.store(midiNote, std::memory_order_relaxed);
    tuningState.isInTune.store(std::abs(deviation) < 5.0f, std::memory_order_relaxed);
}
