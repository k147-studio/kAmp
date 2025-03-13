#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "Pedalboard.h"
#include "EffectComponent.h"

class PedalboardComponent : public EffectComponent {
  public:
    PedalboardComponent(AbstractEffect* pedalboard);
    ~PedalboardComponent() override;
    void addEffect(EffectComponent* effect);
    void resized() override;
    void paint(juce::Graphics &g) override;
    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override;
  private:
    std::vector<juce::Component*> effectsComponents;
    juce::FlexBox flexBox;
};