#include "ConnectionComponent.h"

LoginComponent::LoginComponent() {
  usernameField.setTextToShowWhenEmpty("Username", juce::Colours::grey);
  passwordField.setTextToShowWhenEmpty("Password", juce::Colours::grey);
  passwordField.setPasswordCharacter('*');
  skipButton.setButtonText("Skip");
  loginButton.setButtonText("Login");
  skipButton.onClick = [this] { skipButtonClicked(); };
}

LoginComponent::~LoginComponent() = default;

void LoginComponent::skipButtonClicked() {
  //addAndMakeVisible(new PedalboardComponent(manager.getPedalboard()));
  setVisible(false);
}

void LoginComponent::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::white);
  addAndMakeVisible(usernameField);
  addAndMakeVisible(passwordField);
  addAndMakeVisible(loginButton);
  addAndMakeVisible(skipButton);
}

void LoginComponent::resized() {
    const auto area = getLocalBounds().reduced(50);
    const auto halfWidth = area.getWidth() / 2;
    const auto halfHeight = area.getHeight() / 2;

    usernameField.setBounds(halfWidth - 100, halfHeight - 80, 300, 40);
    passwordField.setBounds(halfWidth - 100, halfHeight - 30, 300, 40);
    loginButton.setBounds(halfWidth - 100, halfHeight + 30, 300, 40);
    skipButton.setBounds(halfWidth - 100, halfHeight + 80, 300, 40);
}