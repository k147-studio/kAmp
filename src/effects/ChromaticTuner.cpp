#include "ChromaticTuner.h"

ChromaticTuner::ChromaticTuner(int fftOrder, double initialSampleRate)
    : fft(fftOrder),
      fftSize(1 << fftOrder),
      sampleRate(initialSampleRate),
      window(static_cast<size_t>(fftSize), juce::dsp::WindowingFunction<float>::hann)
{
    fftBuffer.calloc(static_cast<size_t>(fftSize) * 2);
}

ChromaticTuner::~ChromaticTuner() = default;

std::optional<float> ChromaticTuner::getMainFrequencyFromAudioBlock(const dsp::AudioBlock<float>& block)
{
    if (block.getNumChannels() == 0)
        return std::nullopt;

    const auto numSamples = block.getNumSamples();
    if (numSamples != static_cast<size_t>(fftSize))
    {
        fftSize = static_cast<int>(numSamples);
        fftBuffer.calloc(static_cast<size_t>(fftSize) * 2);
    }

    // 1. Copier un bloc mono (moyenne stéréo si besoin)
    for (int i = 0; i < fftSize; ++i)
    {
        float sample = 0.0f;
        for (size_t ch = 0; ch < block.getNumChannels(); ++ch)
            sample += block.getSample(static_cast<int>(ch), i);
        fftBuffer[i] = sample / static_cast<float>(block.getNumChannels());
    }

    // 2. Appliquer fenêtre de Hann
    window.multiplyWithWindowingTable(fftBuffer.get(), static_cast<size_t>(fftSize));

    // 3. Appliquer la FFT
    std::fill(fftBuffer.get() + fftSize, fftBuffer.get() + 2 * fftSize, 0.0f); // imag = 0
    fft.performRealOnlyForwardTransform(fftBuffer.get());

    // 4. Trouver le pic de magnitude dans la plage utile
    int maxIndex = 1;
    float maxMag = 0.0f;

    for (int bin = 1; bin < fftSize / 2; ++bin)
    {
        float real = fftBuffer[2 * bin];
        float imag = fftBuffer[2 * bin + 1];
        float magnitude = std::sqrt(real * real + imag * imag);

        if (magnitude > maxMag)
        {
            maxMag = magnitude;
            maxIndex = bin;
        }
    }

    // 5. Interpolation parabolique pour précision sub-bin
    float alpha = fftBuffer[2 * (maxIndex - 1)];
    float beta  = fftBuffer[2 * maxIndex];
    float gamma = fftBuffer[2 * (maxIndex + 1)];
    float denom = alpha - 2 * beta + gamma;

    float binShift = (denom == 0.0f) ? 0.0f : 0.5f * (alpha - gamma) / denom;
    float interpolatedBin = static_cast<float>(maxIndex) + binShift;

    // 6. Convertir en fréquence
    float frequency = static_cast<float>((interpolatedBin * sampleRate) / fftSize);
    return frequency;
}

int ChromaticTuner::getFFTSize() const
{
    return fftSize;
}