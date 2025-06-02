#include "ToggleButtonComponent.h"

ToggleButtonComponent::ToggleButtonComponent()
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    setSize(100, 50);
}

ToggleButtonComponent::~ToggleButtonComponent() = default;

void ToggleButtonComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(getWidth() / 2 - 25, getHeight() / 2 - 12.5, 50, 25, 10.0f);
    if (getToggleState())
    {
        g.setColour(juce::Colours::green);
        g.fillEllipse(getWidth() / 2, (getHeight() / 2 - 12.5) + 3, 19, 19);
    }
    else
    {
        g.setColour(juce::Colours::red);
        g.fillEllipse(getWidth() / 2 - 22, (getHeight() / 2 - 12.5) + 3, 19, 19);
    }
}