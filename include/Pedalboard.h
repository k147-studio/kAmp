#pragma once

#include "AbstractEffect.h"
#include <juce_audio_utils/juce_audio_utils.h>

class Pedalboard : public AbstractEffect {
  public:
    Pedalboard();
    Pedalboard(const std::vector<AbstractEffect*> &effects);
    ~Pedalboard() override;
    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override;
    bool operator==(const AbstractEffect* effect) override;
    void append(AbstractEffect* effect);
    void insert(AbstractEffect* effect, int index);
    void remove(const AbstractEffect* effect);
    std::vector<AbstractEffect*> getEffects();

  private:
    std::vector<AbstractEffect*> effects;
};