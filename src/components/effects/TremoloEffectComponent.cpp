#include "TremoloEffectComponent.h"

TremoloEffectComponent::TremoloEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), tremoloEffect(dynamic_cast<TremoloEffect*>(e))
{
    jassert(tremoloEffect != nullptr);

    primaryColor = juce::Colours::mediumvioletred;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)) };

    auto configureSlider = [](juce::Slider& slider, double min, double max, double value)
    {
        slider.setSliderStyle(juce::Slider::Rotary);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        slider.setRange(min, max, 0.01);
        slider.setValue(value);
    };

    configureSlider(rateSlider, 0.1, 20.0, tremoloEffect != nullptr ? tremoloEffect->getRate() : 4.0);
    rateSlider.onValueChange = [this]()
    {
        if (tremoloEffect != nullptr)
            tremoloEffect->setRate(static_cast<float>(rateSlider.getValue()));
    };
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType(juce::Justification::centred);

    configureSlider(depthSlider, 0.0, 1.0, tremoloEffect != nullptr ? tremoloEffect->getDepth() : 0.5);
    depthSlider.onValueChange = [this]()
    {
        if (tremoloEffect != nullptr)
            tremoloEffect->setDepth(static_cast<float>(depthSlider.getValue()));
    };
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::centred);

    grid.items.addArray({
        juce::GridItem(rateLabel), juce::GridItem(depthLabel),
        juce::GridItem(rateSlider), juce::GridItem(depthSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(rateSlider);
    settingsLayout->addAndMakeVisible(rateLabel);
    settingsLayout->addAndMakeVisible(depthSlider);
    settingsLayout->addAndMakeVisible(depthLabel);

    initializePedal();
    setSize(300, 300);
}
