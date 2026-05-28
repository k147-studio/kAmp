#include "NoiseGateEffectComponent.h"
#include "NoiseGateEffect.h"

NoiseGateEffectComponent::NoiseGateEffectComponent(AbstractEffect* e): BasePedalComponent(e)
{
    auto* noiseGateEffect = dynamic_cast<NoiseGateEffect*>(e);
    jassert(noiseGateEffect != nullptr);

    primaryColor = juce::Colours::darkslateblue;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(3)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    thresholdSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    thresholdSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    thresholdSlider.setTextValueSuffix("dB");
    thresholdSlider.setTitle("Threshold");
    thresholdSlider.setRange(-100.0f, 0.0f, 0.1f);
    thresholdSlider.setValue(-50.0f);
    if (noiseGateEffect != nullptr)
    {
        thresholdSlider.onValueChange = [this, noiseGateEffect] {
            this->onThreholdValueChanged(noiseGateEffect, thresholdSlider.getValue());
        };
    }

    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.setJustificationType(juce::Justification::centred);
    thresholdLabel.attachToComponent(&thresholdSlider, false);

    attackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    attackSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    attackSlider.setTextValueSuffix(" ms");
    attackSlider.setTitle("Attack");
    attackSlider.setRange(0.0f, 100.0f, 0.1f);
    attackSlider.setValue(10.0f);
    if (noiseGateEffect != nullptr)
    {
        attackSlider.onValueChange = [this, noiseGateEffect] {
            this->onAttackValueChanged(noiseGateEffect, attackSlider.getValue());
        };
    }

    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);
    attackLabel.attachToComponent(&attackSlider, false);

    releaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    releaseSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    releaseSlider.setTextValueSuffix(" ms");
    releaseSlider.setTitle("Release");
    releaseSlider.setRange(0.0f, 1000.0f, 1.0f);
    releaseSlider.setValue(100.0f);
    if (noiseGateEffect != nullptr)
    {
        releaseSlider.onValueChange = [this, noiseGateEffect] {
            this->onReleaseValueChanged(noiseGateEffect, releaseSlider.getValue());
        };
    }

    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.attachToComponent(&releaseSlider, false);

    grid.items = {
        juce::GridItem(thresholdLabel),
        juce::GridItem(attackLabel),
        juce::GridItem(releaseLabel),
        juce::GridItem(thresholdSlider),
        juce::GridItem(attackSlider),
        juce::GridItem(releaseSlider)
    };

    settingsLayout = new PedalSettingsLayoutComponent(&grid);
    settingsLayout->addAndMakeVisible(thresholdSlider);
    settingsLayout->addAndMakeVisible(thresholdLabel);
    settingsLayout->addAndMakeVisible(attackSlider);
    settingsLayout->addAndMakeVisible(attackLabel);
    settingsLayout->addAndMakeVisible(releaseSlider);
    settingsLayout->addAndMakeVisible(releaseLabel);

    initializePedal();
    setSize(300, 300);
}

NoiseGateEffectComponent::~NoiseGateEffectComponent() = default;

void NoiseGateEffectComponent::onThreholdValueChanged(NoiseGateEffect* gateEffect, double value)
{
    gateEffect->setThreshold(static_cast<float>(value));
}

void NoiseGateEffectComponent::onAttackValueChanged(NoiseGateEffect* gateEffect, double value)
{
    gateEffect->setAttack(static_cast<float>(value));
}

void NoiseGateEffectComponent::onReleaseValueChanged(NoiseGateEffect* gateEffect, double value)
{
    gateEffect->setRelease(static_cast<float>(value));
}


