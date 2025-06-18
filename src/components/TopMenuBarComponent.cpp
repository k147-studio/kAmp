#include "TopMenuBarComponent.h"

#include "AccountComponent.h"
#include "ModalOverlayComponent.h"
#include "PopupContentComponent.h"
#include "ResourceManager.h"
#include "SettingsComponent.h"

TopMenuBarComponent::TopMenuBarComponent(AudioDeviceManager &deviceManager, bool *isSoundMuted) {
	this->isSoundMuted = isSoundMuted;

	if (const Image settingsImage = ResourceManager::loadImage("resources/icons/settings.png");
		settingsImage.isValid()) {
		settingsButton.setImages(true, true, true, settingsImage, 1.0f, {}, settingsImage, 1.0f, {}, settingsImage,
								 1.0f, {});
		settingsButton.setSize(settingsImage.getWidth(), settingsImage.getHeight());
		addAndMakeVisible(settingsButton);
	} else {
		DBG("Error: image settings.png not found");
	}

	if (const Image accountImage = ResourceManager::loadImage("resources/icons/account.png"); accountImage.isValid()) {
		accountButton.setImages(true, true, true, accountImage, 1.0f, {}, accountImage, 1.0f, {}, accountImage, 1.0f,
								{});
		accountButton.setSize(accountImage.getWidth(), accountImage.getHeight());
		addAndMakeVisible(accountButton);
	} else {
		DBG("Error: image account.png not found");
	}

	if (const Image muteImage = ResourceManager::loadImage("resources/icons/mute.png"); muteImage.isValid()) {
		muteButton.setImages(true, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
		muteButton.setSize(muteImage.getWidth(), muteImage.getHeight());
		addAndMakeVisible(muteButton);
	} else {
		DBG("Error: image mute.png not found");
	}

	if (const Image exportImage = ResourceManager::loadImage("resources/icons/sync.png"); exportImage.isValid()) {
		exportButton.setImages(true, true, true, exportImage, 1.0f, {}, exportImage, 1.0f, {}, exportImage, 1.0f, {});
		exportButton.setSize(exportImage.getWidth(), exportImage.getHeight());
		addAndMakeVisible(exportButton);
	} else {
		DBG("Error: image sync.png not found");
	}

#if !JUCE_IOS
	settingsButton.onClick = [this, &deviceManager]() { openSettingsPopup(deviceManager); };
#endif
	accountButton.onClick = [this] { openAccountPopup(); };
	muteButton.onClick = [this] { toggleMute(); };
	exportButton.onClick = [] { DBG("export button clicked"); };

	flexBox.alignItems = FlexBox::AlignItems::center;
	flexBox.justifyContent = FlexBox::JustifyContent::flexEnd;

	flexBox.items.add(FlexItem(muteButton).withWidth(buttonSize).withHeight(buttonSize).withMargin({0, gap, 0, 0}));
	flexBox.items.add(FlexItem(exportButton).withWidth(buttonSize).withHeight(buttonSize).withMargin({0, gap, 0, 0}));
	flexBox.items.add(FlexItem(settingsButton).withWidth(buttonSize).withHeight(buttonSize).withMargin({0, gap, 0, 0}));
	flexBox.items.add(FlexItem(accountButton).withWidth(buttonSize).withHeight(buttonSize).withMargin({0, gap, 0, 0}));
}

TopMenuBarComponent::~TopMenuBarComponent() = default;

void TopMenuBarComponent::paint(Graphics &g) {
	ColourGradient gradient(Colours::black, 0, 0, Colours::transparentBlack, 0, static_cast<float>(getHeight()), false);
	g.setGradientFill(gradient);
	g.fillAll();

	// Draw "kAmp" in bold italic in the left corner
	const Font font("Times New Roman", 24.0f, Font::bold | Font::italic);
	g.setFont(font);
	g.setColour(Colours::white);

	int leftMargin = 16;
	int topMargin = (getHeight() - 24) / 2;
	g.drawText("kAmp", leftMargin, topMargin, 80, 24, Justification::left);
}

void TopMenuBarComponent::resized() {
	auto const *mainWindow = getTopLevelComponent();
	if (mainWindow == nullptr)
		return;

	if (modalOverlay != nullptr)
		modalOverlay->setBounds(mainWindow->getLocalBounds());

	if (settingsComponent != nullptr)
		settingsComponent->setBounds(mainWindow->getLocalBounds());

	if (accountComponent != nullptr)
		accountComponent->setBounds(mainWindow->getLocalBounds());

	flexBox.performLayout(getLocalBounds());
}

void TopMenuBarComponent::openSettingsPopup(AudioDeviceManager &deviceManager) {
	settingsComponent = std::make_unique<SettingsComponent>(deviceManager);
	auto *mainWindow = getTopLevelComponent();
	if (mainWindow == nullptr)
		return;

	modalOverlay = std::make_unique<ModalOverlayComponent>("Audio settings", settingsComponent.get());
	modalOverlay->setBounds(mainWindow->getLocalBounds());
	mainWindow->addAndMakeVisible(modalOverlay.get());
}

void TopMenuBarComponent::openAccountPopup() {
	accountComponent = std::make_unique<AccountComponent>();
	auto *mainWindow = getTopLevelComponent();
	if (mainWindow == nullptr)
		return;

	modalOverlay = std::make_unique<ModalOverlayComponent>("Account", accountComponent.get());
	modalOverlay->setBounds(mainWindow->getLocalBounds());
	mainWindow->addAndMakeVisible(modalOverlay.get());
}

void TopMenuBarComponent::toggleMute() {
	if (*this->isSoundMuted) {
		if (Image muteImage = ResourceManager::loadImage("resources/icons/unmute.png"); muteImage.isValid()) {
			muteButton.setImages(false, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
			addAndMakeVisible(muteButton);
		} else {
			DBG("Error: image mute.png not found");
		}
	} else {
		if (Image muteImage = ResourceManager::loadImage("resources/icons/mute.png"); muteImage.isValid()) {
			muteButton.setImages(false, true, true, muteImage, 1.0f, {}, muteImage, 1.0f, {}, muteImage, 1.0f, {});
			addAndMakeVisible(muteButton);
		} else {
			DBG("Error: image mute.png not found");
		}
	}
	*this->isSoundMuted = !*this->isSoundMuted;
}
