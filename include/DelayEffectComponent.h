#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include "BasePedalComponent.h"
#include "DelayEffect.h"

/**
 * @brief Represents a graphical component that contains and displays a delay effect.
 */
class DelayEffectComponent : public BasePedalComponent {
  public:
    /**
     * @brief Initializes a new instance of the DelayComponent class.
     */
    DelayEffectComponent();

    /**
     * @brief Initializes a new instance of the DelayComponent class with the given AbstractEffect.
     * @param effect The effect to initialize the component with.
     */
    explicit DelayEffectComponent(AbstractEffect* effect);

    /**
     * @brief Destroys the instance of the DelayComponent class.
     */
    ~DelayEffectComponent() override;

  private:
    /**
     * @brief The grid that contains the subcomponents of the delay effect
     * and determines their layout.
     */
    juce::Grid grid;

    /**
     * @brief The slider that controls the rate of the delay effect.
     */
    juce::Slider rateSlider;

    /**
	* @brief The label of the rate slider.
	*/
    juce::Label rateLabel;

    /**
     * @brief The slider that controls the delay of the delay effect.
     */
    juce::Slider delaySlider;

    /**
	* @brief The label of the delay slider.
	*/
    juce::Label delayLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayEffectComponent)
};