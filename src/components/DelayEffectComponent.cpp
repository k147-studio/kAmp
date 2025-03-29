#include "DelayEffectComponent.h"

DelayEffectComponent::DelayEffectComponent() : EffectComponent(new DelayEffect()) {}

DelayEffectComponent::DelayEffectComponent(AbstractEffect* effect) : EffectComponent(effect) {
    if (DelayEffect* delayEffect = dynamic_cast<DelayEffect *>(effect)) {
        using Track = juce::Grid::TrackInfo;
        using Fr = juce::Grid::Fr;
        grid.templateRows = { Track (Fr (1)) };
        grid.templateColumns = { Track (Fr (1)), Track (Fr (1)) };
        grid.items = { juce::GridItem(rateSlider),
                       juce::GridItem(delaySlider) };
        rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        rateSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,false, 100, 20);
        rateSlider.setTextValueSuffix("Hz");
        rateSlider.setTitle("Rate");
        rateSlider.setRange(0.0, 100.0, 1);
        rateSlider.setValue(50.0);
        rateSlider.onValueChange = [this, delayEffect] { delayEffect->setRate(rateSlider.getValue()); };

        rateLabel.setText("Rate", juce::dontSendNotification);
        rateLabel.attachToComponent(&rateSlider, false);

        delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        delaySlider.setTextValueSuffix("ms");
        delaySlider.setTitle("Delay");
        delaySlider.setTextBoxStyle(juce::Slider::TextBoxAbove,false, 100, 20);
        delaySlider.setRange(0.0, 1000.0, 10);
        delaySlider.setValue(500.0);

        delayLabel.setText("Delay", juce::dontSendNotification);
        delayLabel.attachToComponent(&delaySlider, false);
    }
}

DelayEffectComponent::~DelayEffectComponent() = default;

void DelayEffectComponent::resized() {
    rateSlider.setBounds(0, 0, 200, 200);
    delaySlider.setBounds(300, 0, 200, 200);
    rateLabel.setBounds(rateSlider.getX(), rateSlider.getY() + 20, rateSlider.getWidth(), 20);
    delayLabel.setBounds(delaySlider.getX(), delaySlider.getY() + 20, delaySlider.getWidth(), 20);
    grid.performLayout(getLocalBounds());
}

void DelayEffectComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::darkred);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 15);
    addAndMakeVisible(rateSlider);
    addAndMakeVisible(rateLabel);
    addAndMakeVisible(delaySlider);
    addAndMakeVisible(delayLabel);
}