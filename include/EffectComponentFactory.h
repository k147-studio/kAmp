#pragma once

#include "EffectComponent.h"
#include "AbstractEffect.h"

/**
 * @brief Factory class that creates graphical effect components.
 */
class EffectComponentFactory
{
    public:
  /**
   * @brief Creates an effect component for the given AbstractEffect.
   * @param effect The effect to create the component for.
   * @return The created effect component.
   */
  static EffectComponent* CreateEffectComponent(AbstractEffect* effect);
};