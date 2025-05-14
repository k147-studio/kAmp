#include "EffectComponentFactory.h"
#include "AbstractEffect.h"
#include "DelayEffectComponent.h"
#include "DistortionEffectComponent.h"

EffectComponent* EffectComponentFactory::CreateEffectComponent(AbstractEffect* effect) {
    if (dynamic_cast<DelayEffect*>(effect) == nullptr) {
        return new DelayEffectComponent(effect);
    }
    if (dynamic_cast<DistortionEffect*>(effect) == nullptr) {
        return new DistortionEffectComponent(effect);
    }
    return nullptr;
}