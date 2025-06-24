#include "ChorusEffectComponent.h"
#include <juce_gui_basics/juce_gui_basics.h>

ChorusEffectComponent::ChorusEffectComponent(AbstractEffect* e)
    : BasePedalComponent(e), chorusEffect(dynamic_cast<ChorusEffect*>(e))
{
    jassert(chorusEffect != nullptr);

    primaryColor = juce::Colours::cornflowerblue;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    // ----- Sliders -----
    // Depth
    depthSlider.setSliderStyle(juce::Slider::Rotary);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
	depthSlider.setColour(Slider::textBoxOutlineColourId,
							 Colours::transparentWhite);
    depthSlider.setRange(0.0, 1.0, 0.01);
    depthSlider.setValue(chorusEffect->getDepth());
    depthSlider.onValueChange = [this]() {
        chorusEffect->setDepth(depthSlider.getValue());
    };
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::centred);

    // Rate
    rateSlider.setSliderStyle(juce::Slider::Rotary);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
	rateSlider.setColour(Slider::textBoxOutlineColourId,
							 Colours::transparentWhite);
    rateSlider.setRange(0.0, 10.0, 0.01);
    rateSlider.setValue(chorusEffect->getRate());
    rateSlider.onValueChange = [this]() {
        chorusEffect->setRate(rateSlider.getValue());
    };
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType(juce::Justification::centred);

    // Mix
    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
	mixSlider.setColour(Slider::textBoxOutlineColourId,
							 Colours::transparentWhite);
    mixSlider.setRange(0.0, 1.0, 0.01);
    mixSlider.setValue(chorusEffect->getMix());
    mixSlider.onValueChange = [this]() {
        chorusEffect->setMix(mixSlider.getValue());
    };
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);

    // ----- Ajouter au Grid -----
    grid.items.addArray({
        juce::GridItem(depthLabel), juce::GridItem(rateLabel), juce::GridItem(mixLabel),
        juce::GridItem(depthSlider), juce::GridItem(rateSlider), juce::GridItem(mixSlider),
    });

    settingsLayout = new PedalSettingsLayoutComponent(&grid);

    addAndMakeVisible(settingsLayout);  // <<== Ajout crucial pour afficher le layout

    if (chorusEffect != nullptr)
    {
        double defaultSampleRate = 44100.0;
        int defaultBlockSize = 512;
        int defaultNumChannels = 2;

        chorusEffect->prepare(defaultSampleRate, defaultBlockSize, defaultNumChannels);
    }

    // Ajout visible
    addAndMakeVisible(depthSlider);
    addAndMakeVisible(depthLabel);
    addAndMakeVisible(rateSlider);
    addAndMakeVisible(rateLabel);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(mixLabel);

    // Positionnement manuel (à ajuster en fonction de ta taille)
    auto area = getLocalBounds();
    int sliderWidth = area.getWidth() / 3;
    int sliderHeight = area.getHeight() / 2;

    depthSlider.setBounds(0, sliderHeight, sliderWidth, sliderHeight);
    depthLabel.setBounds(0, 0, sliderWidth, sliderHeight / 2);

    rateSlider.setBounds(sliderWidth, sliderHeight, sliderWidth, sliderHeight);
    rateLabel.setBounds(sliderWidth, 0, sliderWidth, sliderHeight / 2);

    mixSlider.setBounds(sliderWidth * 2, sliderHeight, sliderWidth, sliderHeight);
    mixLabel.setBounds(sliderWidth * 2, 0, sliderWidth, sliderHeight / 2);


    this->initializePedal();
    setSize(300, 300);
}



