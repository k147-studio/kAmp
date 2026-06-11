#pragma once

#include "BasePedalComponent.h"
#include "TremoloEffect.h"

#include <juce_gui_basics/juce_gui_basics.h>

class TremoloEffectComponent : public BasePedalComponent
{
public:
    explicit TremoloEffectComponent(AbstractEffect* e);

private:
    TremoloEffect* tremoloEffect;

    juce::Slider rateSlider, depthSlider;
    juce::Label rateLabel, depthLabel;

    juce::Grid grid;
};
