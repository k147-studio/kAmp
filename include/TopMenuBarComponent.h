#pragma once

#include "AccountComponent.h"
#include "ModalOverlayComponent.h"
#include "SettingsComponent.h"

/**
 * @brief Represents a graphical component that contains and displays the top menu bar.
 */

constexpr int buttonSize = 30;
constexpr int gap = 16;

class TopMenuBarComponent : public Component {
public:
	/**
	 * @brief Initializes a new instance of the TopMenuBarComponent class.
	 */
	explicit TopMenuBarComponent(AudioDeviceManager &deviceManager, bool *isSoundMuted = nullptr);

	/**
	 * @brief Destroys the instance of the TopMenuBarComponent class.
	 */
	~TopMenuBarComponent() override;

	/**
	 * @brief Determines how to display the component.
	 * @param g The JUCE graphics context that paints the component.
	 */
	void paint(Graphics &g) override;

	/**
	 * @brief Determines what to do when the component is resized.
	 */
	void resized() override;

private:
	/**
	 * @brief The flexBox component that contains the menu items.
	 */
	FlexBox flexBox;

	ImageButton accountButton;
	ImageButton exportButton;
	ImageButton muteButton;
	ImageButton settingsButton;

	std::unique_ptr<SettingsComponent> settingsComponent;
	std::unique_ptr<AccountComponent> accountComponent;
	std::unique_ptr<ModalOverlayComponent> modalOverlay;

	bool *isSoundMuted = nullptr;

	void openSettingsPopup(AudioDeviceManager &deviceManager);

	void openAccountPopup();

	void toggleMute();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopMenuBarComponent)
};
