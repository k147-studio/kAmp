#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class PopupWindow : public juce::DocumentWindow
{
public:
    PopupWindow(const juce::String& name, juce::Component* contentToShow)
        : DocumentWindow(name, juce::Colours::darkgrey, DocumentWindow::closeButton)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(contentToShow, true);
        setResizable(false, false);
        centreWithSize(400, 300);
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        // Ferme la fenêtre
        setVisible(false);
        delete this;
    }
};
