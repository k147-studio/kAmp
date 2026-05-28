#include "BasePedalComponent.h"

#include "AppFonts.h"
#include "PedalboardComponent.h"
#include "ResourceManager.h"

BasePedalComponent::BasePedalComponent(AbstractEffect* e) :
	EffectComponent(e) {
	setInterceptsMouseClicks(true, false);
	addMouseListener(this, true);
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
	const bool enabled = !getEffect()->getEnabled();
	getEffect()->setEnabled(enabled);
	enablePedalButton.setToggleState(enabled, dontSendNotification);
	isEnabledIndicator->togglePower(enabled);
}

void BasePedalComponent::initializePedal() {
	jassert(settingsLayout != nullptr);

	isEnabledIndicator = new PedalPowerIndicatorComponent(getEffect()->getEnabled());
	pedalLabel = new Label();
	pedalLabel->setText(getEffect()->effectName, dontSendNotification);
	pedalLabel->setJustificationType(Justification::centred);
	pedalLabel->setFont(AppFonts::bold(30.0f));

	ResourceManager::configureIconButton(enablePedalButton, ResourceManager::getPowerIcon());
	enablePedalButton.onClick = [this] {
		this->onEnableButtonClicked();
	};
	addAndMakeVisible(enablePedalButton);

	addAndMakeVisible(*settingsLayout);
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

void BasePedalComponent::mouseDown(const MouseEvent& event) {
	if (dynamic_cast<Label*>(event.eventComponent) || dynamic_cast<
		    PedalPowerIndicatorComponent*>(event.eventComponent)) {
		if (auto* parent = getParentComponent())
			if (auto* dnd = dynamic_cast<DragAndDropContainer*>(parent))
				dnd->startDragging("Pedal", this);
	}
}

bool BasePedalComponent::isInterestedInDragSource(
	const SourceDetails& details) {
	return details.description == "Pedal";
}

void BasePedalComponent::itemDropped(const SourceDetails& details) {
	if (auto* parent = dynamic_cast<PedalboardComponent*>(getParentComponent()))
		parent->onPedalDropped(this, details.sourceComponent.get());
}
