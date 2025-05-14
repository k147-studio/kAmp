#pragma once

#include <JuceHeader.h>

class AccountComponent : public Component
{
public:
    AccountComponent();
    void paint(Graphics&) override;
    void resized() override;

private:
    void apiResponseReceived(const String& content);
    Label responseLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AccountComponent)
};
