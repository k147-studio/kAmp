#include "BasePedalComponent.h"

BasePedalComponent::BasePedalComponent(AbstractEffect* effect) : EffectComponent(effect)
{
    isEnabled = effect->isEnabled;
    pedalLabel = new juce::Label();
    pedalLabel->setText(getEffect()->effectName, juce::dontSendNotification);
    pedalLabel->setJustificationType(juce::Justification::centred);
    pedalLabel->setFont(20.0f);
    pedalLabel->setBounds(getWidth() / 2 - 50, 10, 100, 30);
    addAndMakeVisible(pedalLabel);

    Image powerImage = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/icons/power.png")));
    enablePedalButton.setImages(true, true, true, powerImage, 1.0f, {}, powerImage, 1.0f, {}, powerImage, 1.0f, {});
    enablePedalButton.setBounds(getWidth() / 2 - 50, getHeight() - 40, 100, 30);
    enablePedalButton.onClick = [this] {
        this->onEnableButtonClicked();
    };

    addAndMakeVisible(enablePedalButton);
    addAndMakeVisible(settingsLayout);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    pedalLayout.templateRows = {
        Track (Fr (1)),
        Track (Fr (3)),
        Track (Fr (1))
    };
    pedalLayout.templateColumns = { Track (Fr (1)) };

    pedalLayout.items = {
        juce::GridItem(pedalLabel),
        juce::GridItem(settingsLayout),
        juce::GridItem(enablePedalButton)
    };
}

BasePedalComponent::~BasePedalComponent() = default;

void BasePedalComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 15);
}

void BasePedalComponent::resized() {
    pedalLabel->setBounds(0, 0, getWidth(), getHeight() / 5);
    settingsLayout->setBounds(0, getHeight() / 5, getWidth(), (getHeight() / 5) * 3);
    enablePedalButton.setBounds(0, (getHeight() / 5) * 4, getWidth(), getHeight() / 5);
    pedalLayout.performLayout(getLocalBounds());
}

void BasePedalComponent::onEnableButtonClicked() {
    *isEnabled = !(*isEnabled);
    enablePedalButton.setToggleState(*isEnabled, juce::dontSendNotification);
}