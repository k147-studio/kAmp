#pragma once

#include <JuceHeader.h>
#include "BasePedalComponent.h"
#include "ToggleButtonComponent.h"

class DistortionEffectComponent : public BasePedalComponent {
public:
    DistortionEffectComponent();
    explicit DistortionEffectComponent(AbstractEffect* effect);
    ~DistortionEffectComponent() override;

private:
    juce::Grid grid;
    juce::Slider levelSlider, toneSlider, distSlider;
    juce::Label levelLabel, toneLabel, distLabel;
    ToggleButtonComponent turboButton;
    juce::Label turboLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionEffectComponent)
};