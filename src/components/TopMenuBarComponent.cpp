#include "TopMenuBarComponent.h"

TopMenuBarComponent::TopMenuBarComponent() {
    addAndMakeVisible(menuBarComponent);
}

TopMenuBarComponent::~TopMenuBarComponent() = default;

void TopMenuBarComponent::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
}

void TopMenuBarComponent::resized() {
    menuBarComponent.setBounds(getLocalBounds());
}