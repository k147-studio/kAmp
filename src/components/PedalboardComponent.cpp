#include "PedalboardComponent.h"

#include "EffectComponentFactory.h"
#include "Pedalboard.h"

PedalboardComponent::PedalboardComponent(Manager& managerToUse)
    : EffectComponent(&managerToUse.getPedalboard()),
      manager(managerToUse)
{
    manager.addChangeListener(this);

    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::center;
    flexBox.alignItems = FlexBox::AlignItems::center;
    flexBox.flexWrap = FlexBox::Wrap::wrap;

    rebuildFromPedalboard();
}

PedalboardComponent::~PedalboardComponent()
{
    manager.removeChangeListener(this);
    clearEffectComponents();
}

void PedalboardComponent::clearEffectComponents()
{
    for (auto* component : effectsComponents)
    {
        removeChildComponent(component);
        delete component;
    }
    effectsComponents.clear();
    preferredSizes.clear();
}

void PedalboardComponent::rebuildFromPedalboard()
{
    clearEffectComponents();

    for (const auto& effect : manager.getPedalboard().getEffects())
    {
        auto* component = EffectComponentFactory::CreateEffectComponent(effect.get());
        jassert(component != nullptr);
        if (component == nullptr)
            continue;

        // Capture constructor setSize() before any FlexBox layout can zero bounds.
        preferredSizes.push_back({ component->getWidth(), component->getHeight() });
        addEffect(component);
    }

    refreshFlexBox();
}

void PedalboardComponent::changeListenerCallback(ChangeBroadcaster*)
{
    rebuildFromPedalboard();

    for (auto* parent = getParentComponent(); parent != nullptr; parent = parent->getParentComponent())
        parent->resized();
}

void PedalboardComponent::resized()
{
    // Never lay out into an empty box — FlexBox would squash children to 0x0,
    // which then breaks getRequiredHeight() and clips wrapped pedals.
    if (getWidth() <= 0 || getHeight() <= 0)
        return;

    flexBox.performLayout(getLocalBounds());
}

void PedalboardComponent::paint(Graphics&) {}

void PedalboardComponent::addEffect(EffectComponent* effectComponent)
{
    if (effectComponent == nullptr)
        return;

    effectsComponents.push_back(effectComponent);
    addAndMakeVisible(effectComponent);
}

int PedalboardComponent::getRequiredWidth() const
{
    int totalWidth = 0;
    for (size_t i = 0; i < preferredSizes.size(); ++i)
        totalWidth += preferredSizes[i].width + PEDALS_MARGIN * 2;
    return totalWidth;
}

int PedalboardComponent::getRequiredHeight(const int boardWidth) const
{
    if (preferredSizes.empty())
        return 0;

    int x = 0;
    int maxHeightInRow = 0;
    int totalHeight = 0;

    for (const auto& size : preferredSizes)
    {
        const int effectWidth = size.width + PEDALS_MARGIN * 2;
        const int effectHeight = size.height + PEDALS_MARGIN * 2;

        if (x + effectWidth > boardWidth && x > 0)
        {
            totalHeight += maxHeightInRow;
            x = 0;
            maxHeightInRow = 0;
        }

        x += effectWidth;
        if (effectHeight > maxHeightInRow)
            maxHeightInRow = effectHeight;
    }

    return totalHeight + maxHeightInRow;
}

void PedalboardComponent::onPedalDropped(Component* target, Component* dragged)
{
    if (target == dragged)
        return;

    auto* targetEffect = dynamic_cast<EffectComponent*>(target);
    auto* draggedEffect = dynamic_cast<EffectComponent*>(dragged);
    if (targetEffect != nullptr && draggedEffect != nullptr)
        onPedalDropped(targetEffect, draggedEffect);
}

void PedalboardComponent::onPedalDropped(EffectComponent* target, EffectComponent* dragged)
{
    if (target == nullptr || dragged == nullptr || target == dragged)
        return;

    manager.move(dragged->getEffect(), target->getEffect());
}

void PedalboardComponent::refreshFlexBox()
{
    flexBox.items.clear();

    for (size_t i = 0; i < effectsComponents.size(); ++i)
    {
        auto* effectComponent = effectsComponents[i];
        const auto size = i < preferredSizes.size()
                              ? preferredSizes[i]
                              : PreferredSize { effectComponent->getWidth(), effectComponent->getHeight() };

        // Restore preferred size in case a previous layout zeroed the component.
        effectComponent->setSize(size.width, size.height);

        flexBox.items.add(FlexItem(*effectComponent)
                              .withWidth(static_cast<float>(size.width))
                              .withHeight(static_cast<float>(size.height))
                              .withMargin(PEDALS_MARGIN));
    }

    resized();
    repaint();
}
