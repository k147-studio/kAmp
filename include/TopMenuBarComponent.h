#pragma once

#include <juce_audio_devices/juce_audio_devices.h>


#include <juce_gui_basics/juce_gui_basics.h>

/**
 * @brief Represents a graphical component that contains and displays the top menu bar.
 */
class TopMenuBarComponent : public juce::Component {
  public:
    /**
     * @brief Initializes a new instance of the TopMenuBarComponent class.
     */
    explicit TopMenuBarComponent(juce::AudioDeviceManager& deviceManager);

    /**
     * @brief Destroys the instance of the TopMenuBarComponent class.
     */
    ~TopMenuBarComponent() override;

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
     * @brief The flexBox component that contains the menu items.
     */
    juce::FlexBox flexBox;

    /**
     * @brief The image button to open settings.
     */
    juce::TextButton settingsButton;
    juce::TextButton accountButton;

    void openSettingsPopup(juce::AudioDeviceManager& deviceManager);
    void openAccountPopup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopMenuBarComponent)
};