#pragma once

#include "AbstractEffect.h"
#include "Pedalboard.h"

#include <functional>
#include <memory>
#include <vector>

struct EffectDescriptor
{
    String type;
    String displayName;
    String category;
    std::function<std::unique_ptr<AbstractEffect>()> make;
};

/**
 * @brief Single registry for creating and serializing effects by type string.
 */
class EffectRegistry
{
public:
    static const std::vector<EffectDescriptor>& getAvailableEffects();
    static std::unique_ptr<AbstractEffect> create(const String& type);
    static std::vector<std::unique_ptr<AbstractEffect>> createDefaultEffects();

    static bool savePedalboard(const Pedalboard& pedalboard, const File& file);
    static bool loadPedalboard(Pedalboard& pedalboard, const File& file);

private:
    EffectRegistry() = delete;
};
