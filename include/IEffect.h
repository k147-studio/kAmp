#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

class IEffect {
  public:
    int id;
    virtual void apply(const juce::AudioSourceChannelInfo &bufferToFill) = 0;
    virtual ~IEffect() = default;
};