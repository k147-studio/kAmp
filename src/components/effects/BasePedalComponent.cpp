#include "BasePedalComponent.h"
#include "ResourceManager.h"

BasePedalComponent::BasePedalComponent(AbstractEffect* effect) :
	EffectComponent(effect) {
	isEnabled = effect->isEnabled;
}

BasePedalComponent::~BasePedalComponent() = default;

void BasePedalComponent::paint(Graphics& g) {
	g.setColour(primaryColor);
	g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 15);
}

void BasePedalComponent::resized() {
	pedalLayout.performLayout(getLocalBounds());
}

void BasePedalComponent::onEnableButtonClicked() {
	*isEnabled = !(*isEnabled);
	enablePedalButton.setToggleState(*isEnabled, dontSendNotification);
	isEnabledIndicator->togglePower(*isEnabled);
}

void BasePedalComponent::initializePedal() {
	isEnabledIndicator = new PedalPowerIndicatorComponent(*isEnabled);
	pedalLabel = new Label();
	pedalLabel->setText(getEffect()->effectName, dontSendNotification);
	pedalLabel->setJustificationType(Justification::centred);
	pedalLabel->setFont(FontOptions(30.0f, Font::bold));

	Image powerImage = ResourceManager::loadImage("resources/icons/power.png");
	if (powerImage.isValid()) {
		enablePedalButton.setImages(true, true, true,
		                            powerImage, 1.0f, {},
		                            powerImage, 1.0f, {},
		                            powerImage, 1.0f, {});
		enablePedalButton.onClick = [this] {
			this->onEnableButtonClicked();
		};
		addAndMakeVisible(enablePedalButton);
	} else {
		DBG("Erreur : image power.png introuvable ou invalide.");
	}

	addAndMakeVisible(*pedalLabel);
	addAndMakeVisible(*isEnabledIndicator);

	using Track = Grid::TrackInfo;
	using Fr = Grid::Fr;
	pedalLayout.templateRows = {
		Track(Fr(2)),
		Track(Fr(1)),
		Track(Fr(1)),
		Track(Fr(1))
	};
	pedalLayout.templateColumns = {
		Track(Fr(1))
	};

	pedalLayout.items = {
		GridItem(*settingsLayout),
		GridItem(enablePedalButton),
		GridItem(*isEnabledIndicator),
		GridItem(*pedalLabel),
	};
}