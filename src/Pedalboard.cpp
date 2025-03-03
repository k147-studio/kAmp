#include "Pedalboard.h"

#include "DelayEffect.h"

Pedalboard::Pedalboard() {
  effects = std::vector<AbstractEffect*>();
  this->append(new DelayEffect());
};

Pedalboard::~Pedalboard() = default;

void Pedalboard::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
  effects = std::vector<AbstractEffect*>();
  if (!effects.empty()) {
    for (AbstractEffect* effect : effects) {
      effect->apply(bufferToFill);
    }
  }
}

void Pedalboard::append(AbstractEffect* effect) {
  effects.push_back(effect);
}

void Pedalboard::insert(AbstractEffect* effect, int index) {
  effects.insert(effects.begin() + index, effect);
}

void Pedalboard::remove(const AbstractEffect* effect) {
  effects.erase(std::remove(effects.begin(), effects.end(), effect), effects.end());
}

std::vector<AbstractEffect*> Pedalboard::getEffects() {
  return effects;
}

Pedalboard::Pedalboard(const std::vector<AbstractEffect*> &effects) {
  this->effects = effects;
}

bool Pedalboard::operator==(const AbstractEffect* effect) {
  return true;
}