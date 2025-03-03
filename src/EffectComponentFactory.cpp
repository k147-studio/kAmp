#include "EffectComponentFactory.h"
#include "AbstractEffect.h"
#include "DelayComponent.h"

EffectComponent* EffectComponentFactory::CreateEffectComponent(AbstractEffect& effect) {
    if (dynamic_cast<DelayEffect&>(effect) == nullptr) {
        return new DelayComponent(&effect);
    }
    return nullptr;
}