#include "PedalboardComponent.h"
#include "EffectComponentFactory.h"

PedalboardComponent::~PedalboardComponent() = default;

PedalboardComponent::PedalboardComponent(AbstractEffect* pedalboard) : EffectComponent(pedalboard) {
    if (Pedalboard* pedalboard = dynamic_cast<Pedalboard*>(this->effect)) {
        for (AbstractEffect *effect : pedalboard->getEffects()) {
            addEffect(EffectComponentFactory::CreateEffectComponent(effect));
        }
    }
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
    flexBox.alignItems = juce::FlexBox::AlignItems::center;
    for (auto &effectComponent : effectsComponents) {
        effectComponent->setSize(200, 300);
        flexBox.items.add(juce::FlexItem(*effectComponent).withWidth(effectComponent->getWidth()).withHeight(effectComponent->getHeight()).withMargin(20));
    }
}

void PedalboardComponent::resized() {
    flexBox.performLayout(getLocalBounds());
}

void PedalboardComponent::paint(juce::Graphics &g) {
}

void PedalboardComponent::addEffect(EffectComponent* effect) {
    effectsComponents.push_back(effect);
    addAndMakeVisible(effect);
}
