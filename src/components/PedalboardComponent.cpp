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