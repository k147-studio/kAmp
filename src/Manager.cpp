#include "Manager.h"

void Manager::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    pedalboard.apply(bufferToFill);
}

void Manager::import() {

}

void Manager::append(AbstractEffect* effect) {
    pedalboard.append(effect);
}

void Manager::exportAll() {

}

void Manager::exportSelection() {

}

Pedalboard Manager::getPedalboard() {
    return pedalboard;
}