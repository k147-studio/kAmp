#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "Pedalboard.h"
#include "EffectComponent.h"

class PedalboardComponent : public juce::Component {
  public:
    PedalboardComponent(Pedalboard pedalboard);
    ~PedalboardComponent() override;
    void addEffect(EffectComponent* effect);
    void resized() override;
    void paint(juce::Graphics &g) override;
  private:
    Pedalboard pedalboard;
    std::vector<juce::Component*> effectsComponents;
};