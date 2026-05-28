#include "EffectComponent.h"
#include "AbstractEffect.h"

EffectComponent::EffectComponent(AbstractEffect* e) : effect(e) {}

AbstractEffect* EffectComponent::getEffect() {
  return effect;
}