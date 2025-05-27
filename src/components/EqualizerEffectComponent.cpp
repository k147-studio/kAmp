#include "EqualizerEffectComponent.h"
#include <juce_gui_basics/juce_gui_basics.h>

#include "EqualizerEffectComponent.h"


EqualizerEffectComponent::EqualizerEffectComponent(AbstractEffect* effect)
    : BasePedalComponent(effect), eqEffect(dynamic_cast<EqualizerEffect*>(effect)) {

    jassert(eqEffect != nullptr);

    primaryColor = juce::Colours::orange;

    const char* freqLabels[10] = { "31Hz", "62Hz", "125Hz", "250Hz", "500Hz", "1k", "2k", "4k", "8k", "16k" };

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    // 2 lignes : sliders + labels
    grid.templateRows = { Track(Fr(4)), Track(Fr(1)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),
                             Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    for (int i = 0; i < 10; ++i) {
        sliders[i].setSliderStyle(juce::Slider::LinearVertical);
        sliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        sliders[i].setRange(-24.0, 24.0, 0.1);
        sliders[i].setValue(0.0);
        sliders[i].setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        sliders[i].onValueChange = [this, i] {
            eqEffect->setGain(i, sliders[i].getValue());
        };
        sliders[i].setTitle(freqLabels[i]);

        labels[i].setText(freqLabels[i], juce::dontSendNotification);
        labels[i].setJustificationType(juce::Justification::centred);
        labels[i].attachToComponent(&sliders[i], false);

        grid.items.add(juce::GridItem(sliders[i]));
        grid.items.add(juce::GridItem(labels[i]));

        addAndMakeVisible(sliders[i]);
        addAndMakeVisible(labels[i]);
    }

    settingsLayout = new PedalSettingsLayoutComponent(&grid);

    setSize(400, 300);
    this->initializePedal();
}



void EqualizerEffectComponent::sliderValueChanged(juce::Slider* slider) {
    for (int i = 0; i < 10; ++i) {
        if (slider == &sliders[i]) {
            eqEffect->setGain(i, slider->getValue());
            break;
        }
    }
}

void EqualizerEffectComponent::resized() {
    auto bounds = getLocalBounds().reduced(10);

    int sliderWidth = bounds.getWidth() / 10;
    int sliderHeight = bounds.getHeight() - 70; // laisser place pour labels + bouton

    // Position sliders et labels
    for (int i = 0; i < 10; ++i) {
        auto sliderArea = bounds.removeFromLeft(sliderWidth);
        sliders[i].setBounds(sliderArea.removeFromTop(sliderHeight));
        labels[i].setBounds(sliderArea);
    }
}
