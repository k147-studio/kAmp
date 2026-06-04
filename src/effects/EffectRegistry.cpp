#include "EffectRegistry.h"

#include "ChorusEffect.h"
#include "DelayEffect.h"
#include "DistortionEffect.h"
#include "EqualizerEffect.h"
#include "NoiseGateEffect.h"

namespace
{
const std::vector<EffectDescriptor>& descriptors()
{
    static const std::vector<EffectDescriptor> table {
        // Dynamics
        { "NoiseGateEffect", "Noise Gate", "Dynamics", [] { return std::make_unique<NoiseGateEffect>(); } },
        // Drive
        { "DistortionEffect", "Distortion", "Drive", [] { return std::make_unique<DistortionEffect>(); } },
        // EQ
        { "EqualizerEffect", "Equalizer", "EQ", [] { return std::make_unique<EqualizerEffect>(); } },
        // Modulation
        { "ChorusEffect", "Chorus", "Modulation", [] { return std::make_unique<ChorusEffect>(); } },
        // Time
        { "DelayEffect", "Delay", "Time", [] { return std::make_unique<DelayEffect>(); } },
    };
    return table;
}
} // namespace

const std::vector<EffectDescriptor>& EffectRegistry::getAvailableEffects()
{
    return descriptors();
}

std::unique_ptr<AbstractEffect> EffectRegistry::create(const String& type)
{
    if (type == "Pedalboard")
        return std::make_unique<Pedalboard>();

    for (const auto& descriptor : descriptors())
    {
        if (descriptor.type == type)
            return descriptor.make();
    }

    return nullptr;
}

std::vector<std::unique_ptr<AbstractEffect>> EffectRegistry::createDefaultEffects()
{
    std::vector<std::unique_ptr<AbstractEffect>> effects;
    effects.push_back(std::make_unique<DelayEffect>());
    effects.push_back(std::make_unique<DistortionEffect>());
    effects.push_back(std::make_unique<EqualizerEffect>());
    effects.push_back(std::make_unique<NoiseGateEffect>());
    effects.push_back(std::make_unique<ChorusEffect>());
    return effects;
}

bool EffectRegistry::savePedalboard(const Pedalboard& pedalboard, const File& file)
{
    DynamicObject::Ptr root = new DynamicObject();
    Array<var> effectsArray;

    for (const auto& effect : pedalboard.getEffects())
        effectsArray.add(effect->toJSON());

    root->setProperty("effects", effectsArray);
    return file.replaceWithText(JSON::toString(var(root.get())));
}

bool EffectRegistry::loadPedalboard(Pedalboard& pedalboard, const File& file)
{
    if (!file.existsAsFile())
        return false;

    const auto rootVar = JSON::parse(file.loadFileAsString());
    const auto* root = rootVar.getDynamicObject();
    if (root == nullptr)
        return false;

    const auto* effectsArray = root->getProperty("effects").getArray();
    if (effectsArray == nullptr)
        return false;

    std::vector<std::unique_ptr<AbstractEffect>> loaded;
    loaded.reserve(static_cast<size_t>(effectsArray->size()));

    for (const auto& effectVar : *effectsArray)
    {
        const auto* effectObj = effectVar.getDynamicObject();
        if (effectObj == nullptr)
            continue;

        const String type = effectObj->getProperty("type").toString();
        auto effect = create(type);
        if (effect == nullptr)
            continue;

        effect->fromJSON(effectVar);
        loaded.push_back(std::move(effect));
    }

    pedalboard.clear();
    pedalboard.appendAll(std::move(loaded));
    return true;
}
