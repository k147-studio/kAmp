// ReverbEffectComponent.h
#pragma once

#include <JuceHeader.h>
#include "BasePedalComponent.h"
#include "ReverbEffect.h"

class ReverbEffectComponent  : public BasePedalComponent
{
public:
    ReverbEffectComponent();

    explicit ReverbEffectComponent(AbstractEffect* effect);

    ~ReverbEffectComponent() override;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbEffectComponent)
};
