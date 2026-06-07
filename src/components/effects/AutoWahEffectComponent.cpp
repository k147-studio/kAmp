#include "AutoWahEffectComponent.h"

AutoWahEffectComponent::AutoWahEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), autoWahEffect(dynamic_cast<AutoWahEffect*>(e))
{
    jassert(autoWahEffect != nullptr);

    primaryColor = juce::Colours::teal;

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

    configureSlider(sensitivitySlider, 0.0, 1.0, autoWahEffect != nullptr ? autoWahEffect->getSensitivity() : 0.5);
    sensitivitySlider.onValueChange = [this]()
    {
        if (autoWahEffect != nullptr)
            autoWahEffect->setSensitivity(static_cast<float>(sensitivitySlider.getValue()));
    };
    sensitivityLabel.setText("Sens", juce::dontSendNotification);
    sensitivityLabel.setJustificationType(juce::Justification::centred);

    configureSlider(rangeSlider, 0.0, 1.0, autoWahEffect != nullptr ? autoWahEffect->getRange() : 0.7);
    rangeSlider.onValueChange = [this]()
    {
        if (autoWahEffect != nullptr)
            autoWahEffect->setRange(static_cast<float>(rangeSlider.getValue()));
    };
    rangeLabel.setText("Range", juce::dontSendNotification);
    rangeLabel.setJustificationType(juce::Justification::centred);

    configureSlider(resonanceSlider, 0.0, 1.0, autoWahEffect != nullptr ? autoWahEffect->getResonance() : 0.5);
    resonanceSlider.onValueChange = [this]()
    {
        if (autoWahEffect != nullptr)
            autoWahEffect->setResonance(static_cast<float>(resonanceSlider.getValue()));
    };
    resonanceLabel.setText("Res", juce::dontSendNotification);
    resonanceLabel.setJustificationType(juce::Justification::centred);

    configureSlider(mixSlider, 0.0, 1.0, autoWahEffect != nullptr ? autoWahEffect->getMix() : 1.0);
    mixSlider.onValueChange = [this]()
    {
        if (autoWahEffect != nullptr)
            autoWahEffect->setMix(static_cast<float>(mixSlider.getValue()));
    };
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);

    grid.items.addArray({
        juce::GridItem(sensitivityLabel), juce::GridItem(rangeLabel),
        juce::GridItem(resonanceLabel), juce::GridItem(mixLabel),
        juce::GridItem(sensitivitySlider), juce::GridItem(rangeSlider),
        juce::GridItem(resonanceSlider), juce::GridItem(mixSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(sensitivitySlider);
    settingsLayout->addAndMakeVisible(sensitivityLabel);
    settingsLayout->addAndMakeVisible(rangeSlider);
    settingsLayout->addAndMakeVisible(rangeLabel);
    settingsLayout->addAndMakeVisible(resonanceSlider);
    settingsLayout->addAndMakeVisible(resonanceLabel);
    settingsLayout->addAndMakeVisible(mixSlider);
    settingsLayout->addAndMakeVisible(mixLabel);

    initializePedal();
    setSize(300, 300);
}
