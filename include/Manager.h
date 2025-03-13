#pragma once

#include "Pedalboard.h"

class Manager {
  public:
    Manager(AbstractEffect* pedalboard);
    void apply(const juce::AudioSourceChannelInfo &bufferToFill);
    void import();
    void append(AbstractEffect* effect);
    void exportAll();
    void exportSelection();
    AbstractEffect* getPedalboard();
  private:
    AbstractEffect* pedalboard;
};