#include "TopMenuBarComponent.h"

TopMenuBarComponent::TopMenuBarComponent() {
  	settingsButton.setButtonText("Settings");
    addAndMakeVisible(settingsButton);
}

TopMenuBarComponent::~TopMenuBarComponent() = default;

void TopMenuBarComponent::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
}

void TopMenuBarComponent::resized() {
    flexBox.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
    flexBox.alignItems = juce::FlexBox::AlignItems::center;

    settingsButton.setBounds(0, 0, 100, 50);

    flexBox.items.add(juce::FlexItem(settingsButton).withWidth(settingsButton.getWidth()).withHeight(settingsButton.getHeight()));
    flexBox.performLayout(getLocalBounds());
}