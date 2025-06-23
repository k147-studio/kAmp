#pragma once

#include <JuceHeader.h>
#include "AccountComponent.h"
#include "ChromaticTunerComponent.h"
#include "ModalOverlayComponent.h"
#include "SettingsComponent.h"

class TopMenuBarComponent : public Component {
public:
	explicit TopMenuBarComponent(AudioDeviceManager& deviceManager,
	                             bool* isMuted = nullptr, std::function<void(const AudioSourceChannelInfo&)>* tuningFunction = nullptr);
	~TopMenuBarComponent() override;

	void paint(Graphics& g) override;
	void resized() override;

private:
	int buttonSize = 32;
	float gap = 16;

	FlexBox flexBox;

	ImageButton accountButton;
	ImageButton muteButton;
	ImageButton settingsButton;
	ImageButton tunerButton;

	AccountComponent* accountComponent;
	ChromaticTunerComponent* tunerComponent;
	ModalOverlayComponent* modalOverlay;
	SettingsComponent* settingsComponent;

	bool* isSoundMuted = nullptr;

	std::function<void(const AudioSourceChannelInfo&)>* tuningFunction;

	void openSettingsPopup(AudioDeviceManager& deviceManager);
	void openAccountPopup();
	void openTunerPopup();
	void toggleMute();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopMenuBarComponent)
};
