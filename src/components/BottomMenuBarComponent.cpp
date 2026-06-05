#include "BottomMenuBarComponent.h"

#include "EffectRegistry.h"

namespace
{
constexpr const char* categoryOrder[] = {
    "Filter",
    "Dynamics",
    "Drive",
    "EQ",
    "Modulation",
    "Time",
};
} // namespace

BottomMenuBarComponent::BottomMenuBarComponent(Manager& managerToUse)
    : manager(managerToUse)
{
    addPedalButton.setButtonText("+");
    addPedalButton.onClick = [this]() { showAddPedalMenu(); };
    addAndMakeVisible(addPedalButton);
}

BottomMenuBarComponent::~BottomMenuBarComponent() = default;

void BottomMenuBarComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::white.withAlpha(0.9f));
}

void BottomMenuBarComponent::resized()
{
    addPedalButton.setBounds(getLocalBounds().reduced(8));
}

void BottomMenuBarComponent::showAddPedalMenu()
{
    juce::PopupMenu menu;
    const auto& effects = EffectRegistry::getAvailableEffects();

    for (const auto* category : categoryOrder)
    {
        juce::PopupMenu categoryMenu;
        bool hasItems = false;

        for (const auto& descriptor : effects)
        {
            if (descriptor.category != category)
                continue;

            hasItems = true;
            categoryMenu.addItem(descriptor.displayName, [this, type = descriptor.type]()
            {
                manager.append(EffectRegistry::create(type));
            });
        }

        if (hasItems)
            menu.addSubMenu(category, categoryMenu);
    }

    menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(addPedalButton));
}
