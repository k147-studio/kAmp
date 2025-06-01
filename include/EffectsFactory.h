#pragma once
#include "AbstractEffect.h"

/**
 * @brief A factory class for creating instances of various effects.
 */
class EffectsFactory
{
public:
    /**
     * @brief Creates one instance of each effect type.
     * @return The vector containing pointers to the created effect instances.
     */
    static std::vector<AbstractEffect*> createAllEffects();
};
