#pragma once

#include "EffectComponent.h"
#include "AbstractEffect.h"

class EffectComponentFactory
{
public:
    static EffectComponent* CreateEffectComponent(AbstractEffect& effect);
};