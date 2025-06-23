#include "AccountComponent.h"
#include "ModalOverlayComponent.h"
#include "PopupContentComponent.h"
#include "ResourceManager.h"
#include "SettingsComponent.h"
#include "TopMenuBarComponent.h"

TopMenuBarComponent::TopMenuBarComponent(AudioDeviceManager& deviceManager, bool* isSoundMuted, std::function<void(const AudioSourceChannelInfo&)>* tuningFunction) {
    this->isSoundMuted = isSoundMuted;
    this->tuningFunction = tuningFunction;
    Image settingsImage = ResourceManager::loadImage("resources/icons/settings.png");
    if (settingsImage.isValid()) {
        settingsButton.setImages(true, true, true, settingsImage, 1.0f, {}, settingsImage, 1.0f, {},settingsImage, 1.0f, {});
        settingsButton.setSize(settingsImage.getWidth(), settingsImage.getHeight());
        addAndMakeVisible(settingsButton);
    } else {
        DBG("Erreur : image settings.png introuvable ou invalide.");
    }

	Image accountImage = ResourceManager::loadImage(
		"resources/icons/account.png");
	if (accountImage.isValid()) {
		accountButton.setImages(true, true, true, accountImage, 1.0f, {},
		                        accountImage, 1.0f, {}, accountImage, 1.0f, {});
		accountButton.setSize(accountImage.getWidth(),
		                      accountImage.getHeight());
		addAndMakeVisible(accountButton);
	} else {
		DBG("Erreur : image account.png introuvable ou invalide.");
	}

	Image muteImage = ResourceManager::loadImage("resources/icons/unmute.png");
	if (muteImage.isValid()) {
		muteButton.setImages(true, true, true, muteImage, 1.0f, {}, muteImage,
		                     1.0f, {}, muteImage, 1.0f, {});
		muteButton.setSize(muteImage.getWidth(), muteImage.getHeight());
		addAndMakeVisible(muteButton);
	} else {
		DBG("Erreur : image mute.png introuvable ou invalide.");
	}

	Image tunerImage = ResourceManager::loadImage("resources/icons/tuner.png");
	if (tunerImage.isValid()) {
		tunerButton.setImages(true, true, true, tunerImage, 1.0f, {},  tunerImage, 1.0f, {}, tunerImage, 1.0f, {});
		tunerButton.setSize(tunerImage.getWidth(), tunerImage.getHeight());
		addAndMakeVisible(tunerButton);
	} else {
		DBG("Erreur : image tuner.png introuvable ou invalide.");
	}

#if !JUCE_IOS
	settingsButton.onClick = [this, &deviceManager] {
		openSettingsPopup(deviceManager);
	};
#endif
	accountButton.onClick = [this] { openAccountPopup(); };
	muteButton.onClick = [this] { toggleMute(); };
	tunerButton.onClick = [this] { openTunerPopup(); };

	flexBox.justifyContent = FlexBox::JustifyContent::flexEnd;
	flexBox.alignItems = FlexBox::AlignItems::center;
	flexBox.items.add(
			FlexItem(tunerButton).withWidth(buttonSize).withHeight(buttonSize).
								 withMargin({0, gap, 0, 0}));
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
    if (mainWindow == nullptr) return;
    if (modalOverlay != nullptr) {
        modalOverlay->setBounds(mainWindow->getLocalBounds());
    }
    if (settingsComponent != nullptr) {
        settingsComponent->setBounds(mainWindow->getLocalBounds());
    }
    if (accountComponent != nullptr) {
        accountComponent->setBounds(mainWindow->getLocalBounds());
    }
    if (tunerComponent != nullptr)    {
        tunerComponent->setBounds(mainWindow->getLocalBounds());
    }
    flexBox.performLayout(getLocalBounds());
}

void TopMenuBarComponent::openSettingsPopup(AudioDeviceManager& deviceManager) {
	settingsComponent = new SettingsComponent(deviceManager);
	auto* mainWindow = getTopLevelComponent();
	if (mainWindow == nullptr) return;

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
		Image muteImage = ResourceManager::loadImage(
			"resources/icons/unmute.png");
		if (muteImage.isValid()) {
			muteButton.setImages(false, true, true, muteImage, 1.0f, {},
			                     muteImage, 1.0f, {}, muteImage, 1.0f, {});
			addAndMakeVisible(muteButton);
		} else {
			DBG("Erreur : image mute.png introuvable ou invalide.");
		}
	} else {
		Image muteImage =
			ResourceManager::loadImage("resources/icons/mute.png");
		if (muteImage.isValid()) {
			muteButton.setImages(false, true, true, muteImage, 1.0f, {},
			                     muteImage, 1.0f, {}, muteImage, 1.0f, {});
			addAndMakeVisible(muteButton);
		} else {
			DBG("Erreur : image mute.png introuvable ou invalide.");
		}
	}
	*this->isSoundMuted = !*this->isSoundMuted;
}

void TopMenuBarComponent::openTunerPopup() {
    tunerComponent = new ChromaticTunerComponent(44100, 9); // Sample rate and FFT order can be adjusted as needed
    auto* mainWindow = getTopLevelComponent();
    if (mainWindow == nullptr)
        return;

    *this->tuningFunction = [&](const AudioSourceChannelInfo& buffer) {
        if (tunerComponent != nullptr)
            tunerComponent->tune(buffer);
    };

    modalOverlay = new ModalOverlayComponent("Chromatic Tuner", tunerComponent);
    modalOverlay->setBounds(mainWindow->getLocalBounds());
	mainWindow->addAndMakeVisible(modalOverlay);
}