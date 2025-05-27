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
    grid.templateRows = { Track(Fr(1)), Track(Fr(3)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),
                             Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    for (int i = 0; i < 10; ++i) {
        sliders[i].setSliderStyle(juce::Slider::LinearVertical);
        sliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        sliders[i].setRange(-24.0, 24.0, 0.1);
        sliders[i].setValue(0.0);
        sliders[i].setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        sliders[i].onValueChange = [this, i]
        {
            if (static_cast<float>(sliders[i].getValue())) {
                eqEffect->setGain(i, static_cast<float>(sliders[i].getValue()));
            }
        };
        sliders[i].setTitle(freqLabels[i]);
        sliders[i].setBounds(i * (getWidth() / 10), 0, getWidth() / 10, (getHeight() / 5) * 4);

        labels[i].setText(freqLabels[i], juce::dontSendNotification);
        labels[i].setJustificationType(juce::Justification::centred);
        labels[i].attachToComponent(&sliders[i], false);
        labels[i].setBounds(i * (getWidth() / 10), 0, getWidth() / 10, getHeight() / 5);

        addAndMakeVisible(sliders[i]);
        addAndMakeVisible(labels[i]);
    }

    for (int i = 0; i < 10; ++i)
    {
        grid.items.add(GridItem(labels[i]));
    }
    for (int i = 0; i < 10; ++i)
    {
        grid.items.add(juce::GridItem(sliders[i]));
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