#pragma once

#include <JuceHeader.h>
#include "AbstractEffect.h"
#include <atomic>

/**
 * @brief Represents a delay effect that applies a delay to the audio stream.
 * Inherits from the AbstractEffect class.
 */
class DelayEffect : public AbstractEffect {
public:
	DelayEffect();
	~DelayEffect() override;

	void apply(const AudioSourceChannelInfo& bufferToFill) override;
	void prepare(const juce::dsp::ProcessSpec& spec) override;
	void reset() override;

	void setRate(float rate);
	void setDelay(float delay);

	[[nodiscard]] float getRate() const noexcept;
	[[nodiscard]] float getDelay() const noexcept;

	bool operator==(const AbstractEffect* effect) override;

	[[nodiscard]] String getEffectType() const override {
		return "DelayEffect";
	}

	[[nodiscard]] var toJSON() const override {
		auto obj = AbstractEffect::toJSON();
		if (auto* dynamicObj = obj.getDynamicObject()) {
			dynamicObj->setProperty("rate", getRate());
			dynamicObj->setProperty("delay", getDelay());
		}
		return obj;
	}

	void fromJSON(const var& json) override {
		AbstractEffect::fromJSON(json);

		if (const auto* obj = json.getDynamicObject()) {
			setRate(static_cast<float>(obj->getProperty("rate")));
			setDelay(static_cast<float>(obj->getProperty("delay")));
		}
	}

private:
	static constexpr float maxDelayMs = 3000.0f;

	void resizeBuffer();

	std::atomic<float> rate { 50.0f };
	std::atomic<float> delay { 500.0f };

	juce::CriticalSection bufferLock;
	double sampleRate = 44100.0;
	std::vector<float> circularBuffer;
	int bufferCapacity = 0;
	int writePosition = 0;
};
