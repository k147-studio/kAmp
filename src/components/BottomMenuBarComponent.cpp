#include "BottomMenuBarComponent.h"

BottomMenuBarComponent::BottomMenuBarComponent() {
    addAndMakeVisible(menuBarComponent);
}

BottomMenuBarComponent::~BottomMenuBarComponent() = default;

void BottomMenuBarComponent::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
}

void BottomMenuBarComponent::resized() {
    menuBarComponent.setBounds(getLocalBounds());
}