#include "DelayEffect.h"
#include "DistortionEffect.h"
#include "Pedalboard.h"
#include "EqualizerEffect.h"
#include "NoiseGateEffect.h"

Pedalboard::Pedalboard() { };

Pedalboard::~Pedalboard() {
  for (AbstractEffect* effect : effects) {
    delete effect;
  }
};

void Pedalboard::apply(const AudioSourceChannelInfo &bufferToFill) {
    for (AbstractEffect* effect : effects) {
      if (*(effect->isEnabled))
      {
        effect->apply(bufferToFill);
      }
    }
}

void Pedalboard::prepare(const juce::dsp::ProcessSpec& spec) {
  for (AbstractEffect* effect : effects) {
    effect->prepare(spec);
  }
}

void Pedalboard::append(AbstractEffect* effect) {
  effects.push_back(effect);
}

void Pedalboard::appendAll(std::vector<AbstractEffect*> effects) {
  this->effects.insert(this->effects.end(), effects.begin(), effects.end());
}

void Pedalboard::insert(AbstractEffect* effect, int index) {
  effects.insert(effects.begin() + index, effect);
}

void Pedalboard::remove(const AbstractEffect* effect) {
  effects.erase(std::remove(effects.begin(), effects.end(), effect), effects.end());
}

std::vector<AbstractEffect*>& Pedalboard::getEffects() {
  return effects;
}

Pedalboard::Pedalboard(const std::vector<AbstractEffect*> &effects) {
  this->effects = effects;
}

bool Pedalboard::operator==(const AbstractEffect* effect) {
  return true;
}