#pragma once

#include "BasePedalComponent.h"
#include "ChorusEffect.h"
#include <juce_gui_basics/juce_gui_basics.h>

class ChorusEffectComponent : public BasePedalComponent
{
public:
    explicit ChorusEffectComponent(AbstractEffect* e);


private:
    ChorusEffect* chorusEffect;

    juce::Slider depthSlider, rateSlider, mixSlider;
    juce::Label depthLabel, rateLabel, mixLabel;

    juce::Grid grid;
};
