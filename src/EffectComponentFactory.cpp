#include "AbstractEffect.h"
#include "DelayEffectComponent.h"
#include "DistortionEffect.h"
#include "DistortionEffectComponent.h"
#include "EffectComponentFactory.h"
#include "EqualizerEffect.h"
#include "EqualizerEffectComponent.h"
#include "NoiseGateEffect.h"
#include "NoiseGateEffectComponent.h"

EffectComponent* EffectComponentFactory::CreateEffectComponent(AbstractEffect* effect) {
    if (dynamic_cast<DelayEffect*>(effect) != nullptr) {
        return new DelayEffectComponent(effect);
    }
    if (dynamic_cast<DistortionEffect*>(effect) != nullptr) {
        return new DistortionEffectComponent(effect);
    }
    if (dynamic_cast<EqualizerEffect*>(effect) != nullptr)
    {
        return new EqualizerEffectComponent(effect);
    }
    if (dynamic_cast<NoiseGateEffect*>(effect) != nullptr) {
        return new NoiseGateEffectComponent(effect);
    }
    return nullptr;
}
