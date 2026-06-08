#include "CompressorEffectComponent.h"

CompressorEffectComponent::CompressorEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), compressorEffect(dynamic_cast<CompressorEffect*>(e))
{
    jassert(compressorEffect != nullptr);

    primaryColor = juce::Colours::darkolivegreen;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    auto configureSlider = [](juce::Slider& slider, double min, double max, double interval, double value)
    {
        slider.setSliderStyle(juce::Slider::Rotary);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        slider.setRange(min, max, interval);
        slider.setValue(value);
    };

    configureSlider(thresholdSlider, -60.0, 0.0, 0.1,
                    compressorEffect != nullptr ? compressorEffect->getThreshold() : -20.0);
    thresholdSlider.onValueChange = [this]()
    {
        if (compressorEffect != nullptr)
            compressorEffect->setThreshold(static_cast<float>(thresholdSlider.getValue()));
    };
    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.setJustificationType(juce::Justification::centred);

    configureSlider(ratioSlider, 1.0, 20.0, 0.1,
                    compressorEffect != nullptr ? compressorEffect->getRatio() : 4.0);
    ratioSlider.onValueChange = [this]()
    {
        if (compressorEffect != nullptr)
            compressorEffect->setRatio(static_cast<float>(ratioSlider.getValue()));
    };
    ratioLabel.setText("Ratio", juce::dontSendNotification);
    ratioLabel.setJustificationType(juce::Justification::centred);

    configureSlider(attackSlider, 0.1, 100.0, 0.1,
                    compressorEffect != nullptr ? compressorEffect->getAttack() : 10.0);
    attackSlider.onValueChange = [this]()
    {
        if (compressorEffect != nullptr)
            compressorEffect->setAttack(static_cast<float>(attackSlider.getValue()));
    };
    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);

    configureSlider(releaseSlider, 10.0, 1000.0, 1.0,
                    compressorEffect != nullptr ? compressorEffect->getRelease() : 100.0);
    releaseSlider.onValueChange = [this]()
    {
        if (compressorEffect != nullptr)
            compressorEffect->setRelease(static_cast<float>(releaseSlider.getValue()));
    };
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);

    configureSlider(levelSlider, 0.0, 24.0, 0.1,
                    compressorEffect != nullptr ? compressorEffect->getLevel() : 0.0);
    levelSlider.onValueChange = [this]()
    {
        if (compressorEffect != nullptr)
            compressorEffect->setLevel(static_cast<float>(levelSlider.getValue()));
    };
    levelLabel.setText("Level", juce::dontSendNotification);
    levelLabel.setJustificationType(juce::Justification::centred);

    grid.items.addArray({
        juce::GridItem(thresholdLabel), juce::GridItem(ratioLabel), juce::GridItem(attackLabel),
        juce::GridItem(releaseLabel), juce::GridItem(levelLabel),
        juce::GridItem(thresholdSlider), juce::GridItem(ratioSlider), juce::GridItem(attackSlider),
        juce::GridItem(releaseSlider), juce::GridItem(levelSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(thresholdSlider);
    settingsLayout->addAndMakeVisible(thresholdLabel);
    settingsLayout->addAndMakeVisible(ratioSlider);
    settingsLayout->addAndMakeVisible(ratioLabel);
    settingsLayout->addAndMakeVisible(attackSlider);
    settingsLayout->addAndMakeVisible(attackLabel);
    settingsLayout->addAndMakeVisible(releaseSlider);
    settingsLayout->addAndMakeVisible(releaseLabel);
    settingsLayout->addAndMakeVisible(levelSlider);
    settingsLayout->addAndMakeVisible(levelLabel);

    initializePedal();
    setSize(500, 300);
}
