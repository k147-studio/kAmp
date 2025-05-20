#pragma once

#include <JuceHeader.h>

#include "BasePedalComponent.h"

/**
 * @brief Represents a graphical component that contains and displays a distortion effect.
 */
class DistortionEffectComponent : public BasePedalComponent {
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

private:
    Grid grid;
    Slider driveSlider;
    Label driveLabel;
    Slider mixSlider;
    Label mixLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionEffectComponent)
};
