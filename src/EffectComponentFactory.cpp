#include "AbstractEffect.h"
#include "ChorusEffectComponent.h"
#include "DelayEffectComponent.h"
#include "DistortionEffectComponent.h"
#include "EffectComponentFactory.h"
#include "EqualizerEffectComponent.h"
#include "NoiseGateEffectComponent.h"

EffectComponent* EffectComponentFactory::CreateEffectComponent(AbstractEffect* effect)
{
    if (effect == nullptr)
        return nullptr;

    // Prefer type string (same source of truth as EffectRegistry) over dynamic_cast.
    const String type = effect->getEffectType();

    if (type == "DelayEffect")
        return new DelayEffectComponent(effect);
    if (type == "DistortionEffect")
        return new DistortionEffectComponent(effect);
    if (type == "EqualizerEffect")
        return new EqualizerEffectComponent(effect);
    if (type == "NoiseGateEffect")
        return new NoiseGateEffectComponent(effect);
    if (type == "ChorusEffect")
        return new ChorusEffectComponent(effect);

    return nullptr;
}
