#include "BasePedalComponent.h"

BasePedalComponent::BasePedalComponent(AbstractEffect* effect) : EffectComponent(effect)
{
    isEnabled = effect->isEnabled;
}

BasePedalComponent::~BasePedalComponent() = default;

void BasePedalComponent::paint(juce::Graphics &g) {
    g.setColour(primaryColor);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 15);
}

void BasePedalComponent::resized() {
    pedalLayout.performLayout(getLocalBounds());
}

void BasePedalComponent::onEnableButtonClicked() {
    *isEnabled = !(*isEnabled);
    enablePedalButton.setToggleState(*isEnabled, juce::dontSendNotification);
    isEnabledIndicator->togglePower(*isEnabled);
}

void BasePedalComponent::initializePedal() {
    isEnabledIndicator = new PedalPowerIndicatorComponent(*isEnabled);
    pedalLabel = new juce::Label();
    pedalLabel->setText(getEffect()->effectName, juce::dontSendNotification);
    pedalLabel->setJustificationType(juce::Justification::centred);
    pedalLabel->setFont(juce::Font(30.0f, juce::Font::bold));

    Image powerImage = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/icons/power.png")));
    enablePedalButton.setImages(true, true, true, powerImage, 1.0f, {}, powerImage, 1.0f, {}, powerImage, 1.0f, {});
    enablePedalButton.onClick = [this] {
        this->onEnableButtonClicked();
    };

    addAndMakeVisible(*pedalLabel);
    addAndMakeVisible(enablePedalButton);
    addAndMakeVisible(*isEnabledIndicator);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    pedalLayout.templateRows = {
        Track (Fr (2)),
        Track (Fr (1)),
        Track (Fr (1)),
        Track (Fr (1))
    };
    pedalLayout.templateColumns = {
        Track (Fr (1))
    };

    pedalLayout.items = {
        juce::GridItem(*settingsLayout),
        juce::GridItem(enablePedalButton),
        juce::GridItem(*isEnabledIndicator),
        juce::GridItem(*pedalLabel),
    };
}