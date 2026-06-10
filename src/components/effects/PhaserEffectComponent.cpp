#include "PhaserEffectComponent.h"

PhaserEffectComponent::PhaserEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), phaserEffect(dynamic_cast<PhaserEffect*>(e))
{
    jassert(phaserEffect != nullptr);

    primaryColor = juce::Colours::mediumorchid;

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

    configureSlider(rateSlider, 0.0, 10.0, 0.01,
                    phaserEffect != nullptr ? phaserEffect->getRate() : 1.0);
    rateSlider.onValueChange = [this]()
    {
        if (phaserEffect != nullptr)
            phaserEffect->setRate(static_cast<float>(rateSlider.getValue()));
    };
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType(juce::Justification::centred);

    configureSlider(depthSlider, 0.0, 1.0, 0.01,
                    phaserEffect != nullptr ? phaserEffect->getDepth() : 0.5);
    depthSlider.onValueChange = [this]()
    {
        if (phaserEffect != nullptr)
            phaserEffect->setDepth(static_cast<float>(depthSlider.getValue()));
    };
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::centred);

    configureSlider(centreFreqSlider, 50.0, 10000.0, 1.0,
                    phaserEffect != nullptr ? phaserEffect->getCentreFrequency() : 1300.0);
    centreFreqSlider.onValueChange = [this]()
    {
        if (phaserEffect != nullptr)
            phaserEffect->setCentreFrequency(static_cast<float>(centreFreqSlider.getValue()));
    };
    centreFreqLabel.setText("Centre Freq", juce::dontSendNotification);
    centreFreqLabel.setJustificationType(juce::Justification::centred);

    configureSlider(feedbackSlider, -1.0, 1.0, 0.01,
                    phaserEffect != nullptr ? phaserEffect->getFeedback() : 0.0);
    feedbackSlider.onValueChange = [this]()
    {
        if (phaserEffect != nullptr)
            phaserEffect->setFeedback(static_cast<float>(feedbackSlider.getValue()));
    };
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centred);

    configureSlider(mixSlider, 0.0, 1.0, 0.01,
                    phaserEffect != nullptr ? phaserEffect->getMix() : 0.5);
    mixSlider.onValueChange = [this]()
    {
        if (phaserEffect != nullptr)
            phaserEffect->setMix(static_cast<float>(mixSlider.getValue()));
    };
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);

    grid.items.addArray({
        juce::GridItem(rateLabel), juce::GridItem(depthLabel), juce::GridItem(centreFreqLabel),
        juce::GridItem(feedbackLabel), juce::GridItem(mixLabel),
        juce::GridItem(rateSlider), juce::GridItem(depthSlider), juce::GridItem(centreFreqSlider),
        juce::GridItem(feedbackSlider), juce::GridItem(mixSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(rateSlider);
    settingsLayout->addAndMakeVisible(rateLabel);
    settingsLayout->addAndMakeVisible(depthSlider);
    settingsLayout->addAndMakeVisible(depthLabel);
    settingsLayout->addAndMakeVisible(centreFreqSlider);
    settingsLayout->addAndMakeVisible(centreFreqLabel);
    settingsLayout->addAndMakeVisible(feedbackSlider);
    settingsLayout->addAndMakeVisible(feedbackLabel);
    settingsLayout->addAndMakeVisible(mixSlider);
    settingsLayout->addAndMakeVisible(mixLabel);

    initializePedal();
    setSize(500, 300);
}
