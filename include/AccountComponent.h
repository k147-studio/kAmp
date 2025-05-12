#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class AccountComponent : public juce::Component
{
public:
    AccountComponent();
    ~AccountComponent() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;
};
