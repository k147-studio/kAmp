#pragma once
#include "BasePedalComponent.h"
#include "NoiseGateEffect.h"
#include <JuceHeader.h>

/**
 * @brief Represents a noise gate effect component that applies a noise gate to the audio stream.
 * Inherits from the BasePedalComponent class.
 */
class NoiseGateEffectComponent: public BasePedalComponent
{
public:
    /**
     * @brief Initializes a new instance of the NoiseGateEffectComponent class.
     */
    explicit NoiseGateEffectComponent(AbstractEffect* effect);

    /**
     * @brief Destroys the instance of the NoiseGateEffectComponent class.
     */
    ~NoiseGateEffectComponent() override;
private:
    /**
     * @brief The Grid component that contains the menu items.
     */
    juce::Grid grid;

    /**
     * @brief The slider that manages the threshold value.
     */
    juce::Slider thresholdSlider;

    /**
     * @brief The label that is linked to the threshold slider.
     */
    juce::Label thresholdLabel;

    /**
     * @brief The slider that manages the attack value.
     */
    juce::Slider attackSlider;

    /**
     * @brief The label that is linked to the attack slider.
     */
    juce::Label attackLabel;

    /**
     * @brief The slider that manages the release value.
     */
    juce::Slider releaseSlider;

    /**
     * @brief The label that is linked to the release slider.
     */
    juce::Label releaseLabel;

    /**
     * @brief The function that is called when the threshold value changes.
     * @param value The new value of the threshold slider.
     */
    void onThreholdValueChanged(NoiseGateEffect* effect, double value);

    /**
     * @brief The function that is called when the release value changes.
     * @param value The new value of the release slider.
     */
    void onAttackValueChanged(NoiseGateEffect* effect, double value);

    /**
     * @brief The function that is called when the release value changes.
     * @param value The new value of the release slider.
     */
    void onReleaseValueChanged(NoiseGateEffect* effect, double value);
};