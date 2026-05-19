#include "Manager.h"
#include "EffectRegistry.h"

Manager::Manager(Pedalboard& pedalboardToManage)
    : pedalboard(pedalboardToManage)
{
}

Pedalboard& Manager::getPedalboard() noexcept
{
    return pedalboard;
}

const Pedalboard& Manager::getPedalboard() const noexcept
{
    return pedalboard;
}

void Manager::append(std::unique_ptr<AbstractEffect> effect)
{
    pedalboard.append(std::move(effect));
    sendChangeMessage();
}

void Manager::remove(const AbstractEffect* effect)
{
    pedalboard.remove(effect);
    sendChangeMessage();
}

void Manager::move(const AbstractEffect* dragged, const AbstractEffect* target)
{
    pedalboard.move(dragged, target);
    sendChangeMessage();
}

bool Manager::importFromFile(const File& file)
{
    if (!EffectRegistry::loadPedalboard(pedalboard, file))
        return false;

    sendChangeMessage();
    return true;
}

bool Manager::exportToFile(const File& file) const
{
    return EffectRegistry::savePedalboard(pedalboard, file);
}
