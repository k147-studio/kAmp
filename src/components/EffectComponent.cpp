#include "EffectComponent.h"
#include "AbstractEffect.h"

EffectComponent::EffectComponent(AbstractEffect* effect) : effect(effect) {
  this->effect = effect;
}

AbstractEffect* EffectComponent::getEffect() {
  return effect;
}