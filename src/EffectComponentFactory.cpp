#include "AbstractEffect.h"
#include "DelayEffectComponent.h"
#include "DistortionEffect.h"
#include "DistortionEffectComponent.h"
#include "EffectComponentFactory.h"

EffectComponent* EffectComponentFactory::CreateEffectComponent(AbstractEffect* effect) {
    if (dynamic_cast<DelayEffect*>(effect) != nullptr) {
        return new DelayEffectComponent(effect);
    }
    if (dynamic_cast<DistortionEffect*>(effect) != nullptr) {
        return new DistortionEffectComponent(effect);
    }
    return nullptr;
}
