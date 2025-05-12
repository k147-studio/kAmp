#include "Manager.h"

Manager::Manager(AbstractEffect* pedalboard) : pedalboard(pedalboard) {

}

void Manager::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    if (bufferToFill.buffer == nullptr) {
        return;
    }
    pedalboard->apply(bufferToFill);
}

void Manager::import() {

}

void Manager::append(AbstractEffect* effect) {
    if (Pedalboard* pedalboard = dynamic_cast<Pedalboard*>(this->pedalboard)) {
        pedalboard->append(effect);
    }
}

void Manager::exportAll() {

}

void Manager::exportSelection() {

}

AbstractEffect* Manager::getPedalboard() {
    return pedalboard;
}