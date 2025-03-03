#include "AudioBuffer.h"

AudioBuffer::AudioBuffer() {}

AudioBuffer::~AudioBuffer() {}

juce::AudioSourceChannelInfo AudioBuffer::getBuffer() {
  return bufferToFill;
}