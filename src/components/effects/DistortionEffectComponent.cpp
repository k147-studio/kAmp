#include "DistortionEffect.h"
#include "DistortionEffectComponent.h"

DistortionEffectComponent::DistortionEffectComponent()
    : BasePedalComponent(new DistortionEffect()) {}

DistortionEffectComponent::DistortionEffectComponent(AbstractEffect* effect)
    : BasePedalComponent(effect)
{
    if (auto* distEffect = dynamic_cast<DistortionEffect*>(effect)) {
        primaryColor = juce::Colours::darkviolet;

        // Level
        levelSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        levelSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        levelSlider.setRange(0.0, 1.0, 0.01);
        levelSlider.setValue(distEffect->getLevel());
        levelSlider.onValueChange = [distEffect, this] {
            distEffect->setLevel(static_cast<float>(levelSlider.getValue()));
        };
        levelLabel.setText("Level", juce::dontSendNotification);
        levelLabel.attachToComponent(&levelSlider, false);
        levelLabel.setJustificationType(juce::Justification::centred);

        // Tone
        toneSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        toneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        toneSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        toneSlider.setRange(0.0, 1.0, 0.01);
        toneSlider.setValue(distEffect->getTone());
        toneSlider.onValueChange = [distEffect, this] {
            distEffect->setTone(static_cast<float>(toneSlider.getValue()));
        };
        toneLabel.setText("Tone", juce::dontSendNotification);
        toneLabel.attachToComponent(&toneSlider, false);
        toneLabel.setJustificationType(juce::Justification::centred);

        // Dist
        distSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        distSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        distSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        distSlider.setRange(0.0, 10.0, 0.01);
        distSlider.setValue(distEffect->getDist());
        distSlider.onValueChange = [distEffect, this] {
            distEffect->setDist(static_cast<float>(distSlider.getValue()));
        };
        distLabel.setText("Dist", juce::dontSendNotification);
        distLabel.attachToComponent(&distSlider, false);
        distLabel.setJustificationType(juce::Justification::centred);

        // Turbo
        turboButton.setToggleState(distEffect->isTurbo(), juce::dontSendNotification);
        turboButton.onClick = [distEffect, this] {
            distEffect->setTurbo(turboButton.getToggleState());
        };

        turboLabel.setText("Turbo", juce::dontSendNotification);
        turboLabel.attachToComponent(&turboButton, false);
        turboLabel.setJustificationType(juce::Justification::centred);

        // Layout
        using Track = juce::Grid::TrackInfo;
        using Fr = juce::Grid::Fr;
        grid.templateRows = { Track (Fr (1)), Track (Fr (3)) };
        grid.templateColumns = { Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)) };
        grid.items = {
            juce::GridItem(toneLabel),
            juce::GridItem(distLabel),
            juce::GridItem(levelLabel),
            juce::GridItem(turboLabel),
            juce::GridItem(toneSlider),
            juce::GridItem(distSlider),
            juce::GridItem(levelSlider),
            juce::GridItem(turboButton)
        };

        settingsLayout = new PedalSettingsLayoutComponent(&grid);

        addAndMakeVisible(levelSlider);
        addAndMakeVisible(levelLabel);
        addAndMakeVisible(toneSlider);
        addAndMakeVisible(toneLabel);
        addAndMakeVisible(distSlider);
        addAndMakeVisible(distLabel);
        addAndMakeVisible(turboButton);
        addAndMakeVisible(turboLabel);

        this->initializePedal();

        setSize(400, DEFAULT_HEIGHT);
    }
}

DistortionEffectComponent::~DistortionEffectComponent() = default;