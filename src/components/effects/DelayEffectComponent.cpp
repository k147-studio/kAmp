#include "DelayEffectComponent.h"

DelayEffectComponent::DelayEffectComponent() : BasePedalComponent(
	new DelayEffect()) {}

DelayEffectComponent::DelayEffectComponent(AbstractEffect* effect) :
	BasePedalComponent(effect) {
	if (auto delayEffect = dynamic_cast<DelayEffect*>(effect)) {
		primaryColor = Colours::mediumblue;
		using Track = Grid::TrackInfo;
		using Fr = Grid::Fr;
		grid.templateRows = {Track(Fr(1)), Track(Fr(3))};
		grid.templateColumns = {Track(Fr(1)), Track(Fr(1))};
		grid.items = {
			GridItem(rateLabel),
			GridItem(delayLabel),
			GridItem(rateSlider),
			GridItem(delaySlider),
		};
		rateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
		rateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
		rateSlider.setColour(Slider::textBoxOutlineColourId,
		                     Colours::transparentWhite);
		rateSlider.setTextValueSuffix("%");
		rateSlider.setTitle("Rate");
		rateSlider.setRange(0.0, 100.0, 1);
		rateSlider.setValue(50.0);
		rateSlider.onValueChange = [this, delayEffect] {
			delayEffect->setRate(rateSlider.getValue());
		};

		rateLabel.setText("Rate", dontSendNotification);
		rateLabel.setJustificationType(Justification::centred);
		rateLabel.attachToComponent(&rateSlider, false);

		delaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
		delaySlider.setTextValueSuffix("ms");
		delaySlider.setTitle("Delay");
		delaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
		delaySlider.setColour(Slider::textBoxOutlineColourId,
		                      Colours::transparentWhite);
		delaySlider.setRange(0.0, 3000.0, 10);
		delaySlider.setValue(500.0);
		delaySlider.onValueChange = [this, delayEffect] {
			delayEffect->setDelay(delaySlider.getValue());
		};

		delayLabel.setText("Delay", dontSendNotification);
		delayLabel.setJustificationType(Justification::centred);
		delayLabel.attachToComponent(&delaySlider, false);

		rateSlider.setBounds(0, 0, 200, 200);
		delaySlider.setBounds(300, 0, 200, 200);
		rateLabel.setBounds(rateSlider.getX(), rateSlider.getY() + 20,
		                    rateSlider.getWidth(), 20);
		delayLabel.setBounds(delaySlider.getX(), delaySlider.getY() + 20,
		                     delaySlider.getWidth(), 20);

		settingsLayout = new PedalSettingsLayoutComponent(&grid);

		addAndMakeVisible(rateSlider);
		addAndMakeVisible(rateLabel);
		addAndMakeVisible(delaySlider);
		addAndMakeVisible(delayLabel);

		this->initializePedal();
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	}
}

DelayEffectComponent::~DelayEffectComponent() = default;