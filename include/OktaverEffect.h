#include "AbstractEffect.h"
#include <juce_dsp/juce_dsp.h>

class OktaverEffect: public AbstractEffect {
public:
	OktaverEffect();
	~OktaverEffect();
	void apply(const AudioSourceChannelInfo& bufferToFill) override;
	float getMix();
	void setMix(float newMix);
	float getOctaveShift();
	void setOctaveShift(float newOctaveShift);

	/**
	 * @brief Compares the effect with another given effect.
	 * @param effect The effect to compare with.
	 * @return True if the effect is equal to the given effect, false otherwise.
	 */
	bool operator==(const AbstractEffect* effect) override;

	/**
	 * @brief Gets the type name of the effect for serialization purposes.
	 * @return A string representing the effect type.
	 */
	[[nodiscard]] String getEffectType() const override {
		return "OktaverEffect";
	}

	/**
	 * @brief Serializes the delay effect to a JSON object.
	 * @return JSON object containing serialized effect data.
	 */
	[[nodiscard]] var toJSON() const override {
		auto obj = AbstractEffect::toJSON();
		if (auto* dynamicObj = obj.getDynamicObject()) {
			dynamicObj->setProperty("mix", mix);
			dynamicObj->setProperty("ocatveShift", octaveShift);
		}
		return obj;
	}

	/**
	 * @brief Deserializes the delay effect from a JSON object.
	 * @param json JSON object containing serialized effect data.
	 */
	void fromJSON(const var& json) override {
		AbstractEffect::fromJSON(json);

		if (const auto* obj = json.getDynamicObject()) {
			mix = static_cast<float>(obj->getProperty("mix"));
			octaveShift = static_cast<float>(obj->getProperty("octaveShift"));
		}
	}
private:
	float mix = 0.5f;
	float octaveShift = 1.0f; // Shift in octaves
};