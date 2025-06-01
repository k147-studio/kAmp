#include "EffectsFactory.h"
#include "DelayEffect.h"
#include "DistortionEffect.h"
#include "EqualizerEffect.h"
#include "NoiseGateEffect.h"

std::vector<AbstractEffect*> EffectsFactory::createAllEffects() {
    std::vector<AbstractEffect*> effects;
    effects.push_back(new DelayEffect());
    effects.push_back(new DistortionEffect());
    effects.push_back(new EqualizerEffect());
    effects.push_back(new NoiseGateEffect());
    return effects;
}
