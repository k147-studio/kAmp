#pragma once

#include <JuceHeader.h>

class ToggleButtonComponent : public ToggleButton
{
public:
    ToggleButtonComponent();
    ~ToggleButtonComponent() override;
    void paint(juce::Graphics& g) override;
};