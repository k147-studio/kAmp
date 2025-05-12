#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include "IEffect.h"
#include "DistortionEffect.h"
#include "EffectComponent.h"

/**
 * @brief Represents a graphical component that contains and displays a distortion effect.
 */
class DistortionEffectComponent : public EffectComponent {
public:
    /**
     * @brief Initializes a new instance of the DistortionEffectComponent class.
     */
    DistortionEffectComponent();

    /**
     * @brief Initializes a new instance of the DistortionEffectComponent class with the given effect.
     * @param effect The effect to initialize the component with.
     */
    explicit DistortionEffectComponent(AbstractEffect* effect);

    /**
     * @brief Destroys the instance of the DistortionEffectComponent class.
     */
    ~DistortionEffectComponent() override;

    /**
     * @brief Called when the component is resized.
     */
    void resized() override;

    /**
     * @brief Paints the component using the JUCE Graphics context.
     * @param g The graphics context.
     */
    void paint(juce::Graphics& g) override;

private:
    juce::Grid grid;
    juce::Slider driveSlider;
    juce::Label driveLabel;
    juce::Slider mixSlider;
    juce::Label mixLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionEffectComponent)
};