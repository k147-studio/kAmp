#include "PedalPowerIndicatorComponent.h"

PedalPowerIndicatorComponent::PedalPowerIndicatorComponent(bool isEnabled)
{
    this->isEnabled = isEnabled;
}

PedalPowerIndicatorComponent::~PedalPowerIndicatorComponent() = default;

void PedalPowerIndicatorComponent::paint(juce::Graphics &g)
{
    g.setColour(isEnabled ? juce::Colours::green : juce::Colours::red);
    g.fillEllipse(juce::Rectangle<float>((getWidth() / 2) - 10,(getHeight() / 2) - 10,20,20));
}

void PedalPowerIndicatorComponent::togglePower(bool isEnabled)
{
    this->isEnabled = isEnabled;
    repaint();
}