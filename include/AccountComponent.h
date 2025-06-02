#pragma once

#include <JuceHeader.h>

class AccountComponent : public juce::Component
{
public:
    AccountComponent();
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void apiResponseReceived(const juce::String& content);
    void saveSettings();
    void importSettings();
    void changePassword();

    juce::Label titleLabel;
    juce::Label responseLabel;

    juce::Label emailLabel, usernameLabel;
    juce::Label emailValueLabel, usernameValueLabel;

    juce::TextButton saveButton, importButton, changePasswordButton;

    juce::Grid grid;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AccountComponent)
};
