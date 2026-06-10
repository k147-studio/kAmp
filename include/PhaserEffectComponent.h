#pragma once

#include "BasePedalComponent.h"
#include "PhaserEffect.h"

#include <juce_gui_basics/juce_gui_basics.h>

class PhaserEffectComponent : public BasePedalComponent
{
public:
    explicit PhaserEffectComponent(AbstractEffect* e);

private:
    PhaserEffect* phaserEffect;

    juce::Slider rateSlider, depthSlider, centreFreqSlider, feedbackSlider, mixSlider;
    juce::Label rateLabel, depthLabel, centreFreqLabel, feedbackLabel, mixLabel;

    juce::Grid grid;
};
