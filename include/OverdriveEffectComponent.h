#pragma once

#include "BasePedalComponent.h"
#include "OverdriveEffect.h"

#include <juce_gui_basics/juce_gui_basics.h>

class OverdriveEffectComponent : public BasePedalComponent
{
public:
    explicit OverdriveEffectComponent(AbstractEffect* e);

private:
    OverdriveEffect* overdriveEffect;

    juce::Slider driveSlider, toneSlider, levelSlider;
    juce::Label driveLabel, toneLabel, levelLabel;

    juce::Grid grid;
};
