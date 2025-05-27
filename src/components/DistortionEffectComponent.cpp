#include "DistortionEffect.h"
#include "DistortionEffectComponent.h"

DistortionEffectComponent::DistortionEffectComponent()
    : BasePedalComponent(new DistortionEffect()) {}

DistortionEffectComponent::DistortionEffectComponent(AbstractEffect* effect)
    : BasePedalComponent(effect)
{
    if (auto* distEffect = dynamic_cast<DistortionEffect*>(effect)) {
        primaryColor = juce::Colours::darkviolet;
        using Track = juce::Grid::TrackInfo;
        using Fr = juce::Grid::Fr;

        grid.templateRows = { Track(Fr(1)), Track(Fr(3)) };
        grid.templateColumns = { Track(Fr(1)) };
        grid.items = {
            juce::GridItem(rangeLabel),
            juce::GridItem(rangeSlider),
        };

        rangeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rangeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
        rangeSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        rangeSlider.setTextValueSuffix("x");
        rangeSlider.setTitle("Range");
        rangeSlider.setRange(0.0000, 1, 0.0001);
        rangeSlider.setValue(0);
        rangeSlider.onValueChange = [this, distEffect] {
            distEffect->setRange(static_cast<float>(rangeSlider.getValue()));
        };

        rangeLabel.setText("Range", juce::dontSendNotification);
        rangeLabel.setJustificationType(juce::Justification::centred);
        rangeLabel.attachToComponent(&rangeSlider, false);


        settingsLayout = new PedalSettingsLayoutComponent(&grid);

        addAndMakeVisible(rangeSlider);
        addAndMakeVisible(rangeLabel);


        setSize(DEFAULT_WIDTH,DEFAULT_HEIGHT);
        this->initializePedal();
    }
}

DistortionEffectComponent::~DistortionEffectComponent() = default;
