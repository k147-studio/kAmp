#include "ReverbEffectComponent.h"

ReverbEffectComponent::ReverbEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), reverbEffect(dynamic_cast<ReverbEffect*>(e))
{
    jassert(reverbEffect != nullptr);

    primaryColor = juce::Colours::cadetblue;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    auto configureSlider = [](juce::Slider& slider, double min, double max, double value)
    {
        slider.setSliderStyle(juce::Slider::Rotary);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        slider.setRange(min, max, 0.01);
        slider.setValue(value);
    };

    configureSlider(mixSlider, 0.0, 1.0, reverbEffect != nullptr ? reverbEffect->getMix() : 0.5);
    mixSlider.onValueChange = [this]()
    {
        if (reverbEffect != nullptr)
            reverbEffect->setMix(static_cast<float>(mixSlider.getValue()));
    };
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);

    configureSlider(sizeSlider, 0.0, 1.0, reverbEffect != nullptr ? reverbEffect->getSize() : 0.5);
    sizeSlider.onValueChange = [this]()
    {
        if (reverbEffect != nullptr)
            reverbEffect->setSize(static_cast<float>(sizeSlider.getValue()));
    };
    sizeLabel.setText("Size", juce::dontSendNotification);
    sizeLabel.setJustificationType(juce::Justification::centred);

    configureSlider(dampSlider, 0.0, 1.0, reverbEffect != nullptr ? reverbEffect->getDamp() : 0.5);
    dampSlider.onValueChange = [this]()
    {
        if (reverbEffect != nullptr)
            reverbEffect->setDamp(static_cast<float>(dampSlider.getValue()));
    };
    dampLabel.setText("Damp", juce::dontSendNotification);
    dampLabel.setJustificationType(juce::Justification::centred);

    configureSlider(widthSlider, 0.0, 1.0, reverbEffect != nullptr ? reverbEffect->getWidth() : 1.0);
    widthSlider.onValueChange = [this]()
    {
        if (reverbEffect != nullptr)
            reverbEffect->setWidth(static_cast<float>(widthSlider.getValue()));
    };
    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centred);

    grid.items.addArray({
        juce::GridItem(mixLabel), juce::GridItem(sizeLabel), juce::GridItem(dampLabel), juce::GridItem(widthLabel),
        juce::GridItem(mixSlider), juce::GridItem(sizeSlider), juce::GridItem(dampSlider), juce::GridItem(widthSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(mixSlider);
    settingsLayout->addAndMakeVisible(mixLabel);
    settingsLayout->addAndMakeVisible(sizeSlider);
    settingsLayout->addAndMakeVisible(sizeLabel);
    settingsLayout->addAndMakeVisible(dampSlider);
    settingsLayout->addAndMakeVisible(dampLabel);
    settingsLayout->addAndMakeVisible(widthSlider);
    settingsLayout->addAndMakeVisible(widthLabel);

    initializePedal();
    setSize(400, 300);
}
