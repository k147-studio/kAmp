#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class LoginComponent final : public juce::Component {
  public:
    LoginComponent();
    ~LoginComponent() override;
    void paint(juce::Graphics &g) override;
    void resized() override;
  private:
    juce::TextEditor usernameField;
    juce::TextEditor passwordField;
    juce::TextButton loginButton;
    juce::TextButton skipButton;

    void skipButtonClicked();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};