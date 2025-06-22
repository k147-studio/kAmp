#include "LoginComponent.h"

LoginComponent::LoginComponent() {
	setupFields();
	setupButtons();
	layoutComponents();
}

LoginComponent::~LoginComponent() = default;

void LoginComponent::setupFields() {
	usernameField.setTextToShowWhenEmpty("Username", Colours::grey);
	passwordField.setTextToShowWhenEmpty("Password", Colours::grey);
	passwordField.setPasswordCharacter('*');
	addAndMakeVisible(usernameField);
	addAndMakeVisible(passwordField);
}

void LoginComponent::setupButtons() {
	loginButton.onClick = [] {
		// TODO: Implement login logic
	};
	skipButton.onClick = [this] { skipButtonClicked(); };
	addAndMakeVisible(loginButton);
	addAndMakeVisible(skipButton);
}

void LoginComponent::paint(Graphics& g) {
	g.fillAll(Colours::white);
}

void LoginComponent::resized() {
	layoutComponents();
}

void LoginComponent::layoutComponents() {
	auto area = getLocalBounds().reduced(50);
	auto halfWidth = area.getWidth() / 2;
	auto halfHeight = area.getHeight() / 2;

	usernameField.setBounds(halfWidth - 100, halfHeight - 80, 300, 40);
	passwordField.setBounds(halfWidth - 100, halfHeight - 30, 300, 40);
	loginButton.setBounds(halfWidth - 100, halfHeight + 30, 300, 40);
	skipButton.setBounds(halfWidth - 100, halfHeight + 80, 300, 40);
}

void LoginComponent::skipButtonClicked() {
	setVisible(false);
}