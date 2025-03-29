#include "EffectComponentFactory.h"
#include "AbstractEffect.h"
#include "DelayEffectComponent.h"

EffectComponent* EffectComponentFactory::CreateEffectComponent(AbstractEffect& effect) {
    if (dynamic_cast<DelayEffect&>(effect) == nullptr) {
        return new DelayEffectComponent(&effect);
    }
    return nullptr;
}