#include "AccountComponent.h"
#include "ModalOverlayComponent.h"
#include "PopupContentComponent.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"
#include "ResourceManager.h"
#include "BinaryData.h"

TopMenuBarComponent::TopMenuBarComponent(AudioDeviceManager& deviceManager,
                                         bool* isMuted) {
	this->isSoundMuted = isMuted;

	juce::Image settingsImage = juce::ImageFileFormat::loadFrom(BinaryData::settings_png, BinaryData::settings_pngSize);
	settingsButton.setImages(true, true, true, settingsImage, 1.0f, {},
								 settingsImage, 1.0f, {}, settingsImage, 1.0f,
								 {});
	addAndMakeVisible(settingsButton);


	juce::Image accountImage = juce::ImageFileFormat::loadFrom(BinaryData::account_png, BinaryData::account_pngSize);
	accountButton.setImages(true, true, true, accountImage, 1.0f, {},
								 accountImage, 1.0f, {}, accountImage, 1.0f,
								 {});
	addAndMakeVisible(accountButton);

	juce::Image muteImage = juce::ImageFileFormat::loadFrom(BinaryData::mute_png, BinaryData::mute_pngSize);
	muteButton.setImages(true, true, true, muteImage, 1.0f, {},
								 muteImage, 1.0f, {}, muteImage, 1.0f,
								 {});
	addAndMakeVisible(muteButton);

#if !JUCE_IOS
	settingsButton.onClick = [this, &deviceManager] {
		openSettingsPopup(deviceManager);
	};
#endif
	accountButton.onClick = [this] { openAccountPopup(); };
	muteButton.onClick = [this] { toggleMute(); };

	flexBox.justifyContent = FlexBox::JustifyContent::flexEnd;
	flexBox.alignItems = FlexBox::AlignItems::center;
	flexBox.items.add(
		FlexItem(muteButton).withWidth(buttonSize).withHeight(buttonSize).
		                     withMargin({0, gap, 0, 0}));
	flexBox.items.add(
		FlexItem(settingsButton).withWidth(buttonSize).withHeight(buttonSize).
		                         withMargin({0, gap, 0, 0}));
	flexBox.items.add(
		FlexItem(accountButton).withWidth(buttonSize).withHeight(buttonSize).
		                        withMargin({0, gap, 0, 0}));
}

TopMenuBarComponent::~TopMenuBarComponent() = default;

void TopMenuBarComponent::paint(Graphics& g) {
	const ColourGradient gradient(Colours::black, 0, 0,
	                              Colours::transparentBlack, 0,
	                              static_cast<float>(getHeight()), false);
	g.setGradientFill(gradient);
	g.fillAll();

	const FontOptions font("Times New Roman", 24.0f, Font::bold | Font::italic);
	g.setFont(font);
	g.setColour(Colours::white);
	const int topMargin = (getHeight() - 24) / 2;

	g.drawText("kAmp", gap, topMargin, 80, 24, Justification::left);
}


void TopMenuBarComponent::resized() {
	auto* mainWindow = getTopLevelComponent();
	if (mainWindow == nullptr)
		return;
	if (modalOverlay != nullptr) {
		modalOverlay->setBounds(mainWindow->getLocalBounds());
	}
	if (settingsComponent != nullptr) {
		settingsComponent->setBounds(mainWindow->getLocalBounds());
	}
	if (accountComponent != nullptr) {
		accountComponent->setBounds(mainWindow->getLocalBounds());
	}
	flexBox.performLayout(getLocalBounds());
}

void TopMenuBarComponent::openSettingsPopup(AudioDeviceManager& deviceManager) {
	settingsComponent = new SettingsComponent(deviceManager);
	auto* mainWindow = getTopLevelComponent();
	if (mainWindow == nullptr)
		return;

	modalOverlay = new ModalOverlayComponent("Audio settings",
	                                         settingsComponent);
	mainWindow->addAndMakeVisible(modalOverlay);
	modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::openAccountPopup() {
	accountComponent = new AccountComponent();
	auto* mainWindow = getTopLevelComponent();
	if (mainWindow == nullptr)
		return;

	modalOverlay = new ModalOverlayComponent("Account", accountComponent);
	mainWindow->addAndMakeVisible(modalOverlay);
	modalOverlay->setBounds(mainWindow->getLocalBounds());
}

void TopMenuBarComponent::toggleMute() {
	if (*this->isSoundMuted) {
		juce::Image muteImage = juce::ImageFileFormat::loadFrom(BinaryData::unmute_png, BinaryData::unmute_pngSize);
		muteButton.setImages(false, true, true, muteImage, 1.0f, {},
									 muteImage, 1.0f, {}, muteImage, 1.0f,
									 {});
		addAndMakeVisible(muteButton);
	} else {
		juce::Image muteImage = juce::ImageFileFormat::loadFrom(BinaryData::mute_png, BinaryData::mute_pngSize);
		muteButton.setImages(false, true, true, muteImage, 1.0f, {},
									 muteImage, 1.0f, {}, muteImage, 1.0f,
									 {});
		addAndMakeVisible(muteButton);
	}
	*(this->isSoundMuted) = !(*(this->isSoundMuted));
}
