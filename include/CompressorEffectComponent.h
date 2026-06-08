#pragma once

#include "BasePedalComponent.h"
#include "CompressorEffect.h"

#include <juce_gui_basics/juce_gui_basics.h>

class CompressorEffectComponent : public BasePedalComponent
{
public:
    explicit CompressorEffectComponent(AbstractEffect* e);

private:
    CompressorEffect* compressorEffect;

    juce::Slider thresholdSlider, ratioSlider, attackSlider, releaseSlider, levelSlider;
    juce::Label thresholdLabel, ratioLabel, attackLabel, releaseLabel, levelLabel;

    juce::Grid grid;
};
