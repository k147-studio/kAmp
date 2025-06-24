#include "OktaverEffect.h"
#include <algorithm>

OktaverEffect::OktaverEffect() {
	effectName = "Oktaver";
}

OktaverEffect::~OktaverEffect() = default;

// C++
void OktaverEffect::apply(const AudioSourceChannelInfo& bufferToFill) {
	auto* buffer = bufferToFill.buffer;
	if (!buffer || buffer->getNumSamples() == 0 || buffer->getNumChannels() == 0)
		return;

	const int numChannels = buffer->getNumChannels();
	const int numSamples = bufferToFill.numSamples;
	float clampedMix = std::clamp(mix, 0.0f, 1.0f);

	float pitchFactor = std::pow(2.0f, -octaveShift / 12.0f);

	for (int channel = 0; channel < 2; ++channel) {
		if (channel >= numChannels) break;
		auto* channelData = buffer->getWritePointer(channel, bufferToFill.startSample);
		std::vector<float> originalData(channelData, channelData + numSamples);
		std::vector<float> shiftedData(numSamples, 0.0f);

		// Resampling avec interpolation linéaire
		for (int i = 0; i < numSamples; ++i) {
			float srcIdx = i / pitchFactor;
			int idx = static_cast<int>(srcIdx);
			float frac = srcIdx - idx;
			if (idx + 1 < numSamples) {
				shiftedData[i] = originalData[idx] * (1.0f - frac) + originalData[idx + 1] * frac;
			} else if (idx < numSamples) {
				shiftedData[i] = originalData[idx];
			}
		}

		// Filtre passe-bas IIR (type RC)
		float alpha = 0.15f; // Plus petit = coupure plus basse
		float y = shiftedData[0];
		for (int i = 1; i < numSamples; ++i) {
			y = alpha * shiftedData[i] + (1.0f - alpha) * y;
			shiftedData[i] = y;
		}

		for (int i = 0; i < numSamples; ++i)
			channelData[i] = (1.0f - clampedMix) * originalData[i] + clampedMix * shiftedData[i];
	}
}


float OktaverEffect::getMix() {
	return mix;
}

void OktaverEffect::setMix(float newMix) {
	if (newMix < 0.0f || newMix > 100.0f) {
		DBG("OktaverEffect::setMix: Invalid mix value, must be between 0.0 and 1.0");
		return;
	}
	mix = newMix;
}

float OktaverEffect::getOctaveShift() {
	return octaveShift;
}

void OktaverEffect::setOctaveShift(float newOctaveShift) {
	if (newOctaveShift < -12.0f || newOctaveShift > 12.0f) {
		DBG("OktaverEffect::setOctaveShift: Invalid octave shift value, must be between -2.0 and 2.0");
		return;
	}
	octaveShift = newOctaveShift;
}

bool OktaverEffect::operator==(const AbstractEffect* effect) {
	return this == effect;
}