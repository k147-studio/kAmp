#pragma once

#include "BasePedalComponent.h"
#include "ReverbEffect.h"

#include <juce_gui_basics/juce_gui_basics.h>

class ReverbEffectComponent : public BasePedalComponent
{
public:
    explicit ReverbEffectComponent(AbstractEffect* e);

private:
    ReverbEffect* reverbEffect;

    juce::Slider mixSlider, sizeSlider, dampSlider, widthSlider;
    juce::Label mixLabel, sizeLabel, dampLabel, widthLabel;

    juce::Grid grid;
};
