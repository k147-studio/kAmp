#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class ConnectionComponent : public juce::Component {
  public:
    ConnectionComponent();
    ~ConnectionComponent();
    void paint(juce::Graphics &g) override;
    void resized() override;
  private:
    juce::TextEditor usernameField;
    juce::TextEditor passwordField;
    juce::TextButton loginButton;
    juce::TextButton skipButton;

    void skipButtonClicked();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ConnectionComponent)
};