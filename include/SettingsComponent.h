#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class SettingsComponent : public juce::Component {
public:
    SettingsComponent() {
        addAndMakeVisible(label);
        label.setText("Réglages", juce::dontSendNotification);
    }

    void resized() override {
        label.setBounds(10, 10, getWidth() - 20, 30);
    }

private:
    juce::Label label;
};


