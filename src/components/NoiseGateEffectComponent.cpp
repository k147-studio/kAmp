#include "NoiseGateEffectComponent.h"
#include "NoiseGateEffect.h"

NoiseGateEffectComponent::NoiseGateEffectComponent(AbstractEffect* effect): BasePedalComponent(effect)
{
    if (NoiseGateEffect* noiseGateEffect = dynamic_cast<NoiseGateEffect*>(effect))
    {
        primaryColor = juce::Colours::darkgrey;
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
        thresholdSlider.onValueChange = [this, noiseGateEffect] {
            this->onThreholdValueChanged(noiseGateEffect, thresholdSlider.getValue());
        };

        thresholdLabel.setText("Threshold", juce::dontSendNotification);
        thresholdLabel.setJustificationType(juce::Justification::centred);
        thresholdLabel.attachToComponent(&thresholdSlider, false);

        attackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
        attackSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        attackSlider.setTextValueSuffix("ms");
        attackSlider.setTitle("Attack");
        attackSlider.setRange(0.0f, 100.0f, 0.1f);
        attackSlider.setValue(10.0f);
        attackSlider.onValueChange = [this, noiseGateEffect] {
            this->onAttackValueChanged(noiseGateEffect, attackSlider.getValue());
        };

        attackLabel.setText("Attack", juce::dontSendNotification);
        attackLabel.setJustificationType(juce::Justification::centred);
        attackLabel.attachToComponent(&attackSlider, false);

        releaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
        releaseSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        releaseSlider.setTextValueSuffix("ms");
        releaseSlider.setTitle("Release");
        releaseSlider.setRange(0.0f, 1000.0f, 1.0f);
        releaseSlider.setValue(100.0f);
        releaseSlider.onValueChange = [this, noiseGateEffect] {
            this->onReleaseValueChanged(noiseGateEffect, releaseSlider.getValue());
        };

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

        this->settingsLayout = new PedalSettingsLayoutComponent(&grid);

        addAndMakeVisible(thresholdSlider);
        addAndMakeVisible(thresholdLabel);
        addAndMakeVisible(attackSlider);
        addAndMakeVisible(attackLabel);
        addAndMakeVisible(releaseSlider);
        addAndMakeVisible(releaseLabel);

        this->initializePedal();
        setSize(300, 300);
    }
}

NoiseGateEffectComponent::~NoiseGateEffectComponent() = default;

void NoiseGateEffectComponent::onThreholdValueChanged(NoiseGateEffect* effect, double value)
{
    if (float threshold = static_cast<float>(value))
    {
        effect->setThreshold(threshold);
    }
}

void NoiseGateEffectComponent::onAttackValueChanged(NoiseGateEffect* effect, double value)
{
    if (float attack = static_cast<float>(value))
    {
        effect->setAttack(attack);
    }
}

void NoiseGateEffectComponent::onReleaseValueChanged(NoiseGateEffect* effect, double value)
{
    if (float release = static_cast<float>(value))
    {
        effect->setRelease(release);
    }
}


