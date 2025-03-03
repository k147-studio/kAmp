#include "ConnectionComponent.h"

ConnectionComponent::ConnectionComponent() {
  usernameField.setTextToShowWhenEmpty("Username", juce::Colours::grey);

  passwordField.setTextToShowWhenEmpty("Password", juce::Colours::grey);
  passwordField.setPasswordCharacter('*');
  skipButton.setButtonText("Skip");
  loginButton.setButtonText("Login");

  addAndMakeVisible(usernameField);
  addAndMakeVisible(passwordField);
  addAndMakeVisible(loginButton);
  addAndMakeVisible(skipButton);

  //loginButton.addListener(this);
  //skipButton.addListener(this);
  skipButton.onClick = [this] { skipButtonClicked(); };
};

ConnectionComponent::~ConnectionComponent() = default;

void ConnectionComponent::skipButtonClicked() {
  //addAndMakeVisible(new PedalboardComponent(manager.getPedalboard()));
  setVisible(false);
}

void ConnectionComponent::paint(juce::Graphics &g) {
  // g.fillAll(juce::Colours::white);
}

void ConnectionComponent::resized() {
    auto area = getLocalBounds().reduced(50);
    auto halfWidth = area.getWidth() / 2;
    auto halfHeight = area.getHeight() / 2;

    usernameField.setBounds(halfWidth - 100, halfHeight - 80, 300, 40);
    passwordField.setBounds(halfWidth - 100, halfHeight - 30, 300, 40);
    loginButton.setBounds(halfWidth - 100, halfHeight + 30, 300, 40);
    skipButton.setBounds(halfWidth - 100, halfHeight + 80, 300, 40);
}