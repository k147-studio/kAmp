#include "PedalboardComponent.h"
#include "EffectComponentFactory.h"

PedalboardComponent::~PedalboardComponent() = default;

PedalboardComponent::PedalboardComponent(Pedalboard pedalboard) : pedalboard(pedalboard) {
    for (AbstractEffect *effect : pedalboard.getEffects()) {
        addEffect(EffectComponentFactory::CreateEffectComponent(*effect));
    }
}

void PedalboardComponent::resized() {
    for (auto &effectComponent : effectsComponents) {
        effectComponent->setSize(200, 300);
    }
}

void PedalboardComponent::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
    for (auto &effectComponent : effectsComponents) {
        addAndMakeVisible(effectComponent);
    }
}

void PedalboardComponent::addEffect(EffectComponent* effect) {
    effectsComponents.push_back(effect);
    addAndMakeVisible(effect);
}