#include "OktaverEffectComponent.h"
#include "OktaverEffect.h"

OktaverEffectComponent::OktaverEffectComponent(AbstractEffect* effect)
	: BasePedalComponent(effect) {
	primaryColor = Colours::darkorange;
	setupSlidersAndLabels();
	using Track = Grid::TrackInfo;
	using Fr = Grid::Fr;
	grid.templateRows = {Track(Fr(1)), Track(Fr(3))};
	grid.templateColumns = {Track(Fr(1)), Track(Fr(1))};
	grid.items = {
		GridItem(mixLabel),
		GridItem(octaveShiftLabel),
		GridItem(mixSlider),
		GridItem(octaveShiftSlider),
	};

	addAndMakeVisible(mixSlider);
	addAndMakeVisible(mixLabel);
	addAndMakeVisible(octaveShiftSlider);
	addAndMakeVisible(octaveShiftLabel);
	setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

	settingsLayout = new PedalSettingsLayoutComponent(&grid);
	this->initializePedal();
}

OktaverEffectComponent::~OktaverEffectComponent() {
	delete settingsLayout;
};

void OktaverEffectComponent::setupSlidersAndLabels() {
	if (auto* oktaver = dynamic_cast<OktaverEffect*>(effect)) {
		mixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
		mixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
		mixSlider.setColour(Slider::textBoxOutlineColourId,
							 Colours::transparentWhite);
		mixSlider.setTextValueSuffix("%");
		mixSlider.setTitle("Mix");
		mixSlider.setRange(0.0, 100.0, 1);
		mixSlider.setValue(50.0);
		mixSlider.onValueChange = [oktaver, this]() {
			oktaver->setMix(mixSlider.getValue());
		};

		mixLabel.setText("Mix", dontSendNotification);
		mixLabel.setJustificationType(Justification::centred);
		mixLabel.attachToComponent(&mixSlider, false);

		octaveShiftSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
		octaveShiftSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
		octaveShiftSlider.setColour(Slider::textBoxOutlineColourId,
							 Colours::transparentWhite);
		octaveShiftSlider.setTextValueSuffix("HT");
		octaveShiftSlider.setTitle("Shift");
		octaveShiftSlider.setRange(-12, 12, 1);
		octaveShiftSlider.setValue(0);
		octaveShiftSlider.onValueChange = [this, oktaver] {
			oktaver->setOctaveShift(octaveShiftSlider.getValue());
		};

		octaveShiftLabel.setText("Shift", dontSendNotification);
		octaveShiftLabel.setJustificationType(Justification::centred);
		octaveShiftLabel.attachToComponent(&octaveShiftSlider, false);
	}
}
