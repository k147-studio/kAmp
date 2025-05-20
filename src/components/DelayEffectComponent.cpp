#include "DelayEffectComponent.h"

DelayEffectComponent::DelayEffectComponent() : BasePedalComponent(new DelayEffect()) {}

DelayEffectComponent::DelayEffectComponent(AbstractEffect* effect) : BasePedalComponent(effect) {
    if (DelayEffect* delayEffect = dynamic_cast<DelayEffect *>(effect)) {
        using Track = juce::Grid::TrackInfo;
        using Fr = juce::Grid::Fr;
        grid.templateRows = { Track (Fr (1)), Track (Fr (3)) };
        grid.templateColumns = { Track (Fr (1)), Track (Fr (1)) };
        grid.items = {
            juce::GridItem(rateLabel),
            juce::GridItem(delayLabel),
            juce::GridItem(rateSlider),
            juce::GridItem(delaySlider),
        };
        rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false, 100, 20);
        rateSlider.setTextValueSuffix("%");
        rateSlider.setTitle("Rate");
        rateSlider.setRange(0.0, 100.0, 1);
        rateSlider.setValue(50.0);
        rateSlider.onValueChange = [this, delayEffect] { delayEffect->setRate(rateSlider.getValue()); };

        rateLabel.setText("Rate", juce::dontSendNotification);
        rateLabel.setJustificationType(Justification::centred);
        rateLabel.attachToComponent(&rateSlider, false);

        delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        delaySlider.setTextValueSuffix("ms");
        delaySlider.setTitle("Delay");
        delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false, 100, 20);
        delaySlider.setRange(0.0, 3000.0, 10);
        delaySlider.setValue(500.0);
        delaySlider.onValueChange = [this, delayEffect] { delayEffect->setDelay(delaySlider.getValue()); };

        delayLabel.setText("Delay", juce::dontSendNotification);
        delayLabel.setJustificationType(Justification::centred);
        delayLabel.attachToComponent(&delaySlider, false);

        settingsLayout = new PedalSettingsLayoutComponent(&grid);

        rateSlider.setBounds(0, 0, 200, 200);
        delaySlider.setBounds(300, 0, 200, 200);
        rateLabel.setBounds(rateSlider.getX(), rateSlider.getY() + 20, rateSlider.getWidth(), 20);
        delayLabel.setBounds(delaySlider.getX(), delaySlider.getY() + 20, delaySlider.getWidth(), 20);

        addAndMakeVisible(rateSlider);
        addAndMakeVisible(rateLabel);
        addAndMakeVisible(delaySlider);
        addAndMakeVisible(delayLabel);
    }
}

DelayEffectComponent::~DelayEffectComponent() = default;