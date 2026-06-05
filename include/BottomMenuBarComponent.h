#pragma once

#include "Manager.h"

#include <juce_gui_basics/juce_gui_basics.h>

/**
 * @brief Bottom bar with an "Add pedal" picker grouped by effect category.
 */
class BottomMenuBarComponent : public juce::Component
{
public:
    explicit BottomMenuBarComponent(Manager& manager);
    ~BottomMenuBarComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void showAddPedalMenu();

    Manager& manager;
    juce::TextButton addPedalButton { "+" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BottomMenuBarComponent)
};
