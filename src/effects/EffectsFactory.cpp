#include "EffectsFactory.h"
#include "DelayEffect.h"
#include "DistortionEffect.h"
#include "EqualizerEffect.h"
#include "NoiseGateEffect.h"
#include "ChorusEffect.h"
#include "ReverbEffect.h"

std::vector<AbstractEffect*> EffectsFactory::createAllEffects() {
    std::vector<AbstractEffect*> effects;
    effects.push_back(new DelayEffect());
    effects.push_back(new DistortionEffect());
    effects.push_back(new EqualizerEffect());
    effects.push_back(new NoiseGateEffect());
    effects.push_back(new ReverbEffect());
    effects.push_back(new ChorusEffect());
    return effects;
}
