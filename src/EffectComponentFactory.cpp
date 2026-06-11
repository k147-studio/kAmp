#include "AbstractEffect.h"
#include "ChorusEffectComponent.h"
#include "AutoWahEffectComponent.h"
#include "CompressorEffectComponent.h"
#include "OverdriveEffectComponent.h"
#include "PhaserEffectComponent.h"
#include "TremoloEffectComponent.h"
#include "DelayEffectComponent.h"
#include "DistortionEffectComponent.h"
#include "EffectComponentFactory.h"
#include "EqualizerEffectComponent.h"
#include "NoiseGateEffectComponent.h"
#include "ReverbEffectComponent.h"

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
    if (type == "ReverbEffect")
        return new ReverbEffectComponent(effect);
    if (type == "AutoWahEffect")
        return new AutoWahEffectComponent(effect);
    if (type == "CompressorEffect")
        return new CompressorEffectComponent(effect);
    if (type == "OverdriveEffect")
        return new OverdriveEffectComponent(effect);
    if (type == "PhaserEffect")
        return new PhaserEffectComponent(effect);
    if (type == "TremoloEffect")
        return new TremoloEffectComponent(effect);

    return nullptr;
}
