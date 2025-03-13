#include "DelayComponent.h"

DelayComponent::DelayComponent() : EffectComponent(new DelayEffect()) {}

DelayComponent::DelayComponent(AbstractEffect* effect) : EffectComponent(effect) {
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
        delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        delaySlider.setTextValueSuffix("ms");
        delaySlider.setTitle("Delay");
        delaySlider.setTextBoxStyle(juce::Slider::TextBoxAbove,false, 100, 20);
        delaySlider.setRange(0.0, 1000.0, 10);
        delaySlider.setValue(500.0);
    }
}

DelayComponent::~DelayComponent() = default;

void DelayComponent::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
    this->effect->apply(bufferToFill);
}

void DelayComponent::resized() {
    rateSlider.setBounds(0, 0, 200, 200);
    delaySlider.setBounds(300, 0, 200, 200);
    grid.performLayout(getLocalBounds());
}

void DelayComponent::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::darkred);
    addAndMakeVisible(rateSlider);
    addAndMakeVisible(delaySlider);
}