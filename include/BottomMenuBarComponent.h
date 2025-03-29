#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

/**
 * @brief Represents a graphical component that contains and displays the bottom menu bar.
 */
class BottomMenuBarComponent : public juce::Component {
  public:
    /**
     * @brief Initializes a new instance of the BottomMenuBarComponent class.
     */
    BottomMenuBarComponent();

    /**
     * @brief Destroys the instance of the BottomMenuBarComponent class.
     */
    ~BottomMenuBarComponent() override;

    /**
     * @brief Determines how to display the component.
     * @param g The JUCE graphics context that paints the component.
     */
    void paint(juce::Graphics &g) override;

    /**
     * @brief Determines what to do when the component is resized.
     */
    void resized() override;
  private:
    /**
     * @brief The menu bar component that contains the menu items.
     */
    juce::MenuBarComponent menuBarComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BottomMenuBarComponent)
};