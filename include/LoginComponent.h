#pragma once

#include <JuceHeader.h>

class LoginComponent final : public Component {
public:
	LoginComponent();
	~LoginComponent() override;

	void paint(Graphics&) override;
	void resized() override;

private:
	void setupFields();
	void setupButtons();
	void layoutComponents();
	void skipButtonClicked();

	TextEditor usernameField;
	TextEditor passwordField;
	TextButton loginButton{"Login"};
	TextButton skipButton{"Skip"};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};