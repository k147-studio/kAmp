#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class PopupContentComponent : public juce::Component
{
public:
    PopupContentComponent()
    {
        setSize(400, 300);

        addAndMakeVisible(closeButton);
        closeButton.setButtonText("Fermer");
        closeButton.onClick = [this]() {
            if (auto* dw = findParentComponentOfClass<juce::DialogWindow>())
                dw->exitModalState(0);
        };
    }

    void resized() override
    {
        closeButton.setBounds(getLocalBounds().reduced(20));
    }

private:
    juce::TextButton closeButton;
};
