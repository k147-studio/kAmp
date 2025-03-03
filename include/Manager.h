#pragma once

#include "Pedalboard.h"

class Manager {
  public:
    void apply(const juce::AudioSourceChannelInfo &bufferToFill);
    void import();
    void append(AbstractEffect* effect);
    void exportAll();
    void exportSelection();
    Pedalboard getPedalboard();
  private:
    Pedalboard pedalboard;
};