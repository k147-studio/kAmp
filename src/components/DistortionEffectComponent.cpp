#include "DistortionEffectComponent.h"

DistortionEffectComponent::DistortionEffectComponent()
    : EffectComponent(new DistortionEffect()) {}

DistortionEffectComponent::DistortionEffectComponent(AbstractEffect* effect)
    : EffectComponent(effect)
{
    if (auto* distEffect = dynamic_cast<DistortionEffect*>(effect)) {
        using Track = juce::Grid::TrackInfo;
        using Fr    = juce::Grid::Fr;

        grid.templateRows    = { Track(Fr(1)) };
        grid.templateColumns = { Track(Fr(1)), Track(Fr(1)) };
        grid.items           = { juce::GridItem(driveSlider), juce::GridItem(mixSlider) };

        driveSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        driveSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 100, 20);
        driveSlider.setTextValueSuffix("x");
        driveSlider.setTitle("Drive");
        driveSlider.setRange(0.0, 10.0, 0.1);
        driveSlider.setValue(1.0);
        driveSlider.onValueChange = [this, distEffect] {
            distEffect->setDrive(static_cast<float>(driveSlider.getValue()));
        };

        driveLabel.setText("Drive", juce::dontSendNotification);
        driveLabel.attachToComponent(&driveSlider, false);

        mixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        mixSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 100, 20);
        mixSlider.setTextValueSuffix("");
        mixSlider.setTitle("Mix");
        mixSlider.setRange(0.0, 1.0, 0.01);
        mixSlider.setValue(0.5);
        mixSlider.onValueChange = [this, distEffect] {
            distEffect->setMix(static_cast<float>(mixSlider.getValue()));
        };

        mixLabel.setText("Mix", juce::dontSendNotification);
        mixLabel.attachToComponent(&mixSlider, false);
    }
}

DistortionEffectComponent::~DistortionEffectComponent() = default;

void DistortionEffectComponent::resized() {
    driveSlider.setBounds(0, 0, 200, 200);
    mixSlider.setBounds(300, 0, 200, 200);
    driveLabel.setBounds(driveSlider.getX(), driveSlider.getY() + 20, driveSlider.getWidth(), 20);
    mixLabel.setBounds(mixSlider.getX(), mixSlider.getY() + 20, mixSlider.getWidth(), 20);
    grid.performLayout(getLocalBounds());
}

void DistortionEffectComponent::paint(juce::Graphics& g) {
    g.setColour(juce::Colours::darkgreen);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 15);
    addAndMakeVisible(driveSlider);
    addAndMakeVisible(driveLabel);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(mixLabel);
}
