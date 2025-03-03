#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include "IEffect.h"
#include "DelayEffect.h"
#include "EffectComponent.h"

class DelayComponent : public EffectComponent {
  public:
    DelayComponent();
    explicit DelayComponent(AbstractEffect* effect);
    ~DelayComponent() override;
    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override;

  private:
    DelayEffect* delayEffect;
    juce::Slider rateSlider;
    juce::Slider delaySlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayComponent)
};