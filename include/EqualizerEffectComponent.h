#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "BasePedalComponent.h"
#include "EqualizerEffect.h"

class EqualizerEffectComponent : public BasePedalComponent {
public:
    explicit EqualizerEffectComponent(AbstractEffect* effect);
    ~EqualizerEffectComponent() override = default;

private:
    EqualizerEffect* eqEffect;
    Slider sliders[10];
    Label labels[10];

    Grid grid;

    void sliderValueChanged(Slider* slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerEffectComponent)
};
