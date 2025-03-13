#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class BottomMenuBarComponent : public juce::Component {
  public:
    BottomMenuBarComponent();
    ~BottomMenuBarComponent();
    void paint(juce::Graphics &g) override;
    void resized() override;
  private:
    juce::MenuBarComponent menuBarComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BottomMenuBarComponent)
};