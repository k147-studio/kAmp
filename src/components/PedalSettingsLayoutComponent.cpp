#include "PedalSettingsLayoutComponent.h"

PedalSettingsLayoutComponent::PedalSettingsLayoutComponent(juce::Grid* layout)
    : layout(layout) {}

PedalSettingsLayoutComponent::~PedalSettingsLayoutComponent() = default;

void PedalSettingsLayoutComponent::paint(juce::Graphics& g) {
}

void PedalSettingsLayoutComponent::resized() {
    layout->performLayout(getLocalBounds());
}