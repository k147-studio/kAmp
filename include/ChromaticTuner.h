#pragma once

#include <JuceHeader.h>

class ChromaticTuner {
public:
	ChromaticTuner(int fftOrder, double sampleRate);
	~ChromaticTuner();
	std::optional<float> getMainFrequencyFromAudioBlock(
		const dsp::AudioBlock<float>& block);
	int getFFTSize() const;

private:
	dsp::FFT fft;
	int fftSize;
	double sampleRate;

	HeapBlock<float> fftBuffer;
	dsp::WindowingFunction<float> window;
};
