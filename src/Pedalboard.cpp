#include "Pedalboard.h"

#include <algorithm>

Pedalboard::Pedalboard() = default;

Pedalboard::~Pedalboard() = default;

void Pedalboard::apply(const AudioSourceChannelInfo& bufferToFill)
{
    const juce::SpinLock::ScopedTryLockType lock(processLock);
    if (!lock.isLocked())
        return;

    for (auto& effect : effects)
    {
        if (effect->getEnabled())
            effect->apply(bufferToFill);
    }
}

void Pedalboard::prepare(const juce::dsp::ProcessSpec& spec)
{
    currentSpec = spec;
    isPrepared = true;

    const juce::SpinLock::ScopedLockType lock(processLock);
    for (auto& effect : effects)
        effect->prepare(spec);
}

void Pedalboard::reset()
{
    const juce::SpinLock::ScopedLockType lock(processLock);
    for (auto& effect : effects)
        effect->reset();
}

bool Pedalboard::operator==(const AbstractEffect* effect)
{
    return this == effect;
}

void Pedalboard::append(std::unique_ptr<AbstractEffect> effect)
{
    if (effect == nullptr)
        return;

    const juce::SpinLock::ScopedLockType lock(processLock);
    if (isPrepared)
        effect->prepare(currentSpec);
    effects.push_back(std::move(effect));
}

void Pedalboard::appendAll(std::vector<std::unique_ptr<AbstractEffect>> newEffects)
{
    for (auto& effect : newEffects)
        append(std::move(effect));
}

void Pedalboard::insert(std::unique_ptr<AbstractEffect> effect, int index)
{
    if (effect == nullptr)
        return;

    const juce::SpinLock::ScopedLockType lock(processLock);
    if (isPrepared)
        effect->prepare(currentSpec);

    const auto clamped = static_cast<size_t>(juce::jlimit(0, static_cast<int>(effects.size()), index));
    effects.insert(effects.begin() + static_cast<std::ptrdiff_t>(clamped), std::move(effect));
}

void Pedalboard::remove(const AbstractEffect* effect)
{
    const juce::SpinLock::ScopedLockType lock(processLock);
    effects.erase(std::remove_if(effects.begin(), effects.end(),
                                 [effect](const std::unique_ptr<AbstractEffect>& owned)
                                 {
                                     return owned.get() == effect;
                                 }),
                  effects.end());
}

void Pedalboard::move(const AbstractEffect* dragged, const AbstractEffect* target)
{
    if (dragged == nullptr || target == nullptr || dragged == target)
        return;

    const juce::SpinLock::ScopedLockType lock(processLock);

    const auto fromIt = std::find_if(effects.begin(), effects.end(),
                                     [dragged](const std::unique_ptr<AbstractEffect>& owned)
                                     {
                                         return owned.get() == dragged;
                                     });
    if (fromIt == effects.end())
        return;

    auto owned = std::move(*fromIt);
    effects.erase(fromIt);

    const auto toIt = std::find_if(effects.begin(), effects.end(),
                                   [target](const std::unique_ptr<AbstractEffect>& candidate)
                                   {
                                       return candidate.get() == target;
                                   });
    if (toIt == effects.end())
    {
        effects.push_back(std::move(owned));
        return;
    }

    effects.insert(toIt, std::move(owned));
}

void Pedalboard::clear()
{
    const juce::SpinLock::ScopedLockType lock(processLock);
    effects.clear();
}

const std::vector<std::unique_ptr<AbstractEffect>>& Pedalboard::getEffects() const noexcept
{
    return effects;
}

std::vector<AbstractEffect*> Pedalboard::getEffectPointers() const
{
    std::vector<AbstractEffect*> pointers;
    pointers.reserve(effects.size());
    for (const auto& effect : effects)
        pointers.push_back(effect.get());
    return pointers;
}

var Pedalboard::toJSON() const
{
    auto root = AbstractEffect::toJSON();
    if (auto* obj = root.getDynamicObject())
    {
        Array<var> children;
        for (const auto& effect : effects)
            children.add(effect->toJSON());
        obj->setProperty("effects", children);
    }
    return root;
}

void Pedalboard::fromJSON(const var& json)
{
    AbstractEffect::fromJSON(json);
    // Child recreation is handled by EffectRegistry / Manager::importFromFile.
}
