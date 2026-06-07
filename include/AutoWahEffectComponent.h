#pragma once

#include "AutoWahEffect.h"
#include "BasePedalComponent.h"

#include <juce_gui_basics/juce_gui_basics.h>

class AutoWahEffectComponent : public BasePedalComponent
{
public:
    explicit AutoWahEffectComponent(AbstractEffect* e);

private:
    AutoWahEffect* autoWahEffect;

    juce::Slider sensitivitySlider, rangeSlider, resonanceSlider, mixSlider;
    juce::Label sensitivityLabel, rangeLabel, resonanceLabel, mixLabel;

    juce::Grid grid;
};
