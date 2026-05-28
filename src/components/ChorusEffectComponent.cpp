#include "ChorusEffectComponent.h"
#include <juce_gui_basics/juce_gui_basics.h>

ChorusEffectComponent::ChorusEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), chorusEffect(dynamic_cast<ChorusEffect*>(e))
{
    jassert(chorusEffect != nullptr);

    primaryColor = juce::Colours::cornflowerblue;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    depthSlider.setSliderStyle(juce::Slider::Rotary);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    depthSlider.setRange(0.0, 1.0, 0.01);
    depthSlider.setValue(chorusEffect != nullptr ? chorusEffect->getDepth() : 0.5);
    depthSlider.onValueChange = [this]() {
        if (chorusEffect != nullptr)
            chorusEffect->setDepth(static_cast<float>(depthSlider.getValue()));
    };
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::centred);

    rateSlider.setSliderStyle(juce::Slider::Rotary);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    rateSlider.setRange(0.0, 10.0, 0.01);
    rateSlider.setValue(chorusEffect != nullptr ? chorusEffect->getRate() : 1.5);
    rateSlider.onValueChange = [this]() {
        if (chorusEffect != nullptr)
            chorusEffect->setRate(static_cast<float>(rateSlider.getValue()));
    };
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType(juce::Justification::centred);

    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mixSlider.setRange(0.0, 1.0, 0.01);
    mixSlider.setValue(chorusEffect != nullptr ? chorusEffect->getMix() : 0.5);
    mixSlider.onValueChange = [this]() {
        if (chorusEffect != nullptr)
            chorusEffect->setMix(static_cast<float>(mixSlider.getValue()));
    };
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);

    grid.items.addArray({
        juce::GridItem(depthLabel), juce::GridItem(rateLabel), juce::GridItem(mixLabel),
        juce::GridItem(depthSlider), juce::GridItem(rateSlider), juce::GridItem(mixSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(depthSlider);
    settingsLayout->addAndMakeVisible(depthLabel);
    settingsLayout->addAndMakeVisible(rateSlider);
    settingsLayout->addAndMakeVisible(rateLabel);
    settingsLayout->addAndMakeVisible(mixSlider);
    settingsLayout->addAndMakeVisible(mixLabel);

    initializePedal();
    setSize(300, 300);
}



