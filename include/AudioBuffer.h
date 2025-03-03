#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

class AudioBuffer {
  public:
    AudioBuffer();
    ~AudioBuffer();
    juce::AudioSourceChannelInfo getBuffer();
  private:
    juce::AudioSourceChannelInfo bufferToFill;
};