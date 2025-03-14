#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "AbstractEffect.h"

class EffectComponent : public juce::Component
{
public:
    virtual void apply(const juce::AudioSourceChannelInfo &bufferToFill) = 0;
protected:
    explicit EffectComponent(AbstractEffect* effect);
    ~EffectComponent() override = default;
    AbstractEffect* effect;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectComponent)
};