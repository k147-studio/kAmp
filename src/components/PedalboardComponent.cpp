#include "PedalboardComponent.h"
#include "EffectComponentFactory.h"

PedalboardComponent::~PedalboardComponent()
{
    for (Component* effectComponent : effectsComponents) {
        removeChildComponent(effectComponent);
        delete effectComponent;
    }
}

PedalboardComponent::PedalboardComponent(AbstractEffect* pedalboard) : EffectComponent(pedalboard) {
    if (Pedalboard* pedalboard = dynamic_cast<Pedalboard*>(this->effect)) {
        for (AbstractEffect *effect : pedalboard->getEffects()) {
            addEffect(EffectComponentFactory::CreateEffectComponent(effect));
        }
    }
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
    flexBox.alignItems = juce::FlexBox::AlignItems::center;
    flexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    for (auto &effectComponent : effectsComponents) {
        flexBox.items.add(juce::FlexItem(*effectComponent).withWidth(effectComponent->getWidth()).withHeight(effectComponent->getHeight()).withMargin(PEDALS_MARGIN));
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


int PedalboardComponent::getRequiredWidth() const {
    int totalWidth = 0;
    for (const auto& effectComponent : effectsComponents) {
        totalWidth += effectComponent->getWidth() + PEDALS_MARGIN * 2;
    }
    return totalWidth;
}

int PedalboardComponent::getRequiredHeight(const int boardWidth) const {
    if (effectsComponents.empty())
        return 0;
    int x = 0;
    int maxHeightInRow = 0;
    int totalHeight = 0;
    const int margin = PEDALS_MARGIN;

    for (const auto* effectComponent : effectsComponents) {
        int effectWidth = effectComponent->getWidth() + margin * 2;
        int effectHeight = effectComponent->getHeight() + margin * 2;

        if (x + effectWidth > boardWidth && x > 0) {
            totalHeight += maxHeightInRow;
            x = 0;
            maxHeightInRow = 0;
        }

        x += effectWidth;
        if (effectHeight > maxHeightInRow)
            maxHeightInRow = effectHeight;
    }

    totalHeight += maxHeightInRow;

    return totalHeight;
}

void PedalboardComponent::onPedalDropped(Component* target, Component* dragged)
{
    if (target == dragged) return;
    if (static_cast<EffectComponent*>(target) != nullptr && static_cast<EffectComponent*>(dragged) != nullptr) {
        onPedalDropped(static_cast<EffectComponent*>(target), static_cast<EffectComponent*>(dragged));
    }
}

void PedalboardComponent::onPedalDropped(EffectComponent* target, EffectComponent* dragged) {
    if (target == dragged) return;

    // Finds the dragged and target components in the effectsComponents vector.
    auto itDragged = std::find(effectsComponents.begin(), effectsComponents.end(), dragged);
    auto itTarget = std::find(effectsComponents.begin(), effectsComponents.end(), target);
    if (itDragged == effectsComponents.end() || itTarget == effectsComponents.end()) return;

    // Reorders the components in the PedalboardComponent.
    auto draggedPtr = *itDragged;
    effectsComponents.erase(itDragged);
    effectsComponents.insert(itTarget, draggedPtr);

    // Reorders the effects in the Pedalboard.
    if (auto* pedalboard = dynamic_cast<Pedalboard*>(effect)) {
        auto& effects = pedalboard->getEffects();
        auto itEffDragged = std::find(effects.begin(), effects.end(), dragged->getEffect());
        auto itEffTarget = std::find(effects.begin(), effects.end(), target->getEffect());
        if (itEffDragged != effects.end() && itEffTarget != effects.end()) {
            auto effPtr = *itEffDragged;
            effects.erase(itEffDragged);
            effects.insert(itEffTarget, effPtr);
        }
    }

    refreshFlexBox();
}

void PedalboardComponent::refreshFlexBox() {
    flexBox.items.clear();
    for (auto &effectComponent : effectsComponents) {
        flexBox.items.add(juce::FlexItem(*effectComponent).withWidth(effectComponent->getWidth()).withHeight(effectComponent->getHeight()).withMargin(PEDALS_MARGIN));
    }
    resized();
    repaint();
}