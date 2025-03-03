#include "DelayComponent.h"

DelayComponent::DelayComponent() : EffectComponent(delayEffect) {
  delayEffect = new DelayEffect();
}

DelayComponent::DelayComponent(AbstractEffect* effect) : EffectComponent(effect) {
    if (auto delayEffect = dynamic_cast<DelayEffect *>(effect)) {
        this->delayEffect = delayEffect;
    }
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    rateSlider.setRange(0.0, 100.0, 1);
    rateSlider.setValue(50.0);
    rateSlider.onValueChange = [this] { delayEffect->setRate(rateSlider.getValue()); };
    addAndMakeVisible(rateSlider);
    delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    delaySlider.setRange(0.0, 1000.0, 10);
    delaySlider.setValue(500.0);
    addAndMakeVisible(delaySlider);
}

DelayComponent::~DelayComponent() {
}

void DelayComponent::apply(const juce::AudioSourceChannelInfo &bufferToFill) {
}