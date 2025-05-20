#include "DistortionEffect.h"
#include "DistortionEffectComponent.h"

DistortionEffectComponent::DistortionEffectComponent()
    : BasePedalComponent(new DistortionEffect()) {}

DistortionEffectComponent::DistortionEffectComponent(AbstractEffect* effect)
    : BasePedalComponent(effect)
{
    if (auto* distEffect = dynamic_cast<DistortionEffect*>(effect)) {
        using Track = juce::Grid::TrackInfo;
        using Fr = juce::Grid::Fr;

        grid.templateRows = { Track(Fr(1)), Track(Fr(3)) };
        grid.templateColumns = { Track(Fr(1)), Track(Fr(1)) };
        grid.items = {
            juce::GridItem(driveLabel),
            juce::GridItem(mixLabel),
            juce::GridItem(driveSlider),
            juce::GridItem(mixSlider),
        };

        driveSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
        driveSlider.setTextValueSuffix("x");
        driveSlider.setTitle("Drive");
        driveSlider.setRange(0.0, 10.0, 0.1);
        driveSlider.setValue(1.0);
        driveSlider.onValueChange = [this, distEffect] {
            distEffect->setDrive(static_cast<float>(driveSlider.getValue()));
        };

        driveLabel.setText("Drive", juce::dontSendNotification);
        driveLabel.setJustificationType(juce::Justification::centred);
        driveLabel.attachToComponent(&driveSlider, false);

        mixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
        mixSlider.setTextValueSuffix("");
        mixSlider.setTitle("Mix");
        mixSlider.setRange(0.0, 1.0, 0.01);
        mixSlider.setValue(0.5);
        mixSlider.onValueChange = [this, distEffect] {
            distEffect->setMix(static_cast<float>(mixSlider.getValue()));
        };

        mixLabel.setText("Mix", juce::dontSendNotification);
        mixLabel.setJustificationType(juce::Justification::centred);
        mixLabel.attachToComponent(&mixSlider, false);

        settingsLayout = new PedalSettingsLayoutComponent(&grid);

        addAndMakeVisible(driveSlider);
        addAndMakeVisible(driveLabel);
        addAndMakeVisible(mixSlider);
        addAndMakeVisible(mixLabel);
    }
}

DistortionEffectComponent::~DistortionEffectComponent() = default;
