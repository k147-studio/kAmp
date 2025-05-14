#include "Manager.h"

Manager::Manager(AbstractEffect *pedalboard) : pedalboard(pedalboard) {
}

void Manager::apply(const juce::AudioSourceChannelInfo &bufferToFill) const {
    if (bufferToFill.buffer == nullptr) {
        return;
    }
    pedalboard->apply(bufferToFill);
}

void Manager::importF() const {
}

void Manager::append(AbstractEffect* effect) const {
    if (Pedalboard* pedalboard = dynamic_cast<Pedalboard*>(this->pedalboard)) {
        pedalboard->append(effect);
    }
}

void Manager::exportAll() const {
}

void Manager::exportSelection() const {
}

AbstractEffect *Manager::getPedalboard() const {
    return pedalboard;
}
