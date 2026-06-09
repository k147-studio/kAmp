#include "OverdriveEffectComponent.h"

OverdriveEffectComponent::OverdriveEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), overdriveEffect(dynamic_cast<OverdriveEffect*>(e))
{
    jassert(overdriveEffect != nullptr);

    primaryColor = juce::Colours::darkorange;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    auto configureSlider = [](juce::Slider& slider, double min, double max, double value)
    {
        slider.setSliderStyle(juce::Slider::Rotary);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        slider.setRange(min, max, 0.01);
        slider.setValue(value);
    };

    configureSlider(driveSlider, 0.0, 1.0, overdriveEffect != nullptr ? overdriveEffect->getDrive() : 0.5);
    driveSlider.onValueChange = [this]()
    {
        if (overdriveEffect != nullptr)
            overdriveEffect->setDrive(static_cast<float>(driveSlider.getValue()));
    };
    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);

    configureSlider(toneSlider, 0.0, 1.0, overdriveEffect != nullptr ? overdriveEffect->getTone() : 0.5);
    toneSlider.onValueChange = [this]()
    {
        if (overdriveEffect != nullptr)
            overdriveEffect->setTone(static_cast<float>(toneSlider.getValue()));
    };
    toneLabel.setText("Tone", juce::dontSendNotification);
    toneLabel.setJustificationType(juce::Justification::centred);

    configureSlider(levelSlider, 0.0, 1.0, overdriveEffect != nullptr ? overdriveEffect->getLevel() : 0.7);
    levelSlider.onValueChange = [this]()
    {
        if (overdriveEffect != nullptr)
            overdriveEffect->setLevel(static_cast<float>(levelSlider.getValue()));
    };
    levelLabel.setText("Level", juce::dontSendNotification);
    levelLabel.setJustificationType(juce::Justification::centred);

    grid.items.addArray({
        juce::GridItem(driveLabel), juce::GridItem(toneLabel), juce::GridItem(levelLabel),
        juce::GridItem(driveSlider), juce::GridItem(toneSlider), juce::GridItem(levelSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(driveSlider);
    settingsLayout->addAndMakeVisible(driveLabel);
    settingsLayout->addAndMakeVisible(toneSlider);
    settingsLayout->addAndMakeVisible(toneLabel);
    settingsLayout->addAndMakeVisible(levelSlider);
    settingsLayout->addAndMakeVisible(levelLabel);

    initializePedal();
    setSize(300, 300);
}
