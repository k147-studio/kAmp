#pragma once

#include <JuceHeader.h>
#include "AccountComponent.h"
#include "ModalOverlayComponent.h"
#include "SettingsComponent.h"
#include "ChromaticTunerComponent.h"

/**
 * @brief Represents a graphical component that contains and displays the top menu bar.
 */
class TopMenuBarComponent : public Component {
public:
	/**
	 * @brief Initializes a new instance of the TopMenuBarComponent class.
	 */
	explicit TopMenuBarComponent(AudioDeviceManager& deviceManager,
	                             bool* isMuted = nullptr,
	                             std::function<void(const juce::AudioSourceChannelInfo&)>* tuningFunction = nullptr);

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
	int buttonSize = 32;
	float gap = 16;

    /**
     * @brief The flexBox component that contains the menu items.
     */
    juce::FlexBox flexBox;

   ModalOverlayComponent* modalOverlay;

    /**
     * @brief The image button to open settings.
     */
    juce::ImageButton settingsButton;
    SettingsComponent* settingsComponent;

    juce::ImageButton accountButton;
    AccountComponent* accountComponent;

    juce::ImageButton tunerButton;
    ChromaticTunerComponent* tunerComponent;
    std::function<void(const juce::AudioSourceChannelInfo&)>* tuningFunction;

    bool* isSoundMuted = nullptr;
    juce::ImageButton muteButton;

    void openSettingsPopup(juce::AudioDeviceManager& deviceManager);
    void openAccountPopup();
    void openTunerPopup();
    void toggleMute();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopMenuBarComponent)
};