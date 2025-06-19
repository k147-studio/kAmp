#include "BasePedalComponent.h"

#include "PedalboardComponent.h"
#include "ResourceManager.h"

BasePedalComponent::BasePedalComponent(AbstractEffect* effect) : EffectComponent(effect)
{
    isEnabled = effect->isEnabled;
    setInterceptsMouseClicks(true, false);
    addMouseListener(this, true);
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

    juce::Image powerImage = ResourceManager::loadImage("resources/icons/power.png");
    if (powerImage.isValid()) {
        enablePedalButton.setImages(true, true, true,
                                    powerImage, 1.0f, {},
                                    powerImage, 1.0f, {},
                                    powerImage, 1.0f, {});
        enablePedalButton.onClick = [this] {
            this->onEnableButtonClicked();
        };
        addAndMakeVisible(enablePedalButton);
    } else {
        DBG("Erreur true: image power.png introuvable ou invalide.");
    }

    addAndMakeVisible(*pedalLabel);
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

void BasePedalComponent::mouseDown(const juce::MouseEvent& event)
{
    if (dynamic_cast<juce::Label*>(event.eventComponent) || dynamic_cast<PedalPowerIndicatorComponent*>(event.eventComponent))
    {
        if (auto* parent = getParentComponent())
            if (auto* dnd = dynamic_cast<juce::DragAndDropContainer*>(parent))
                dnd->startDragging("Pedal", this);
    }
}

bool BasePedalComponent::isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails& details)
{
    return details.description == "Pedal";
}

void BasePedalComponent::itemDropped(const juce::DragAndDropTarget::SourceDetails& details)
{
    if (auto* parent = dynamic_cast<PedalboardComponent*>(getParentComponent()))
        parent->onPedalDropped(this, details.sourceComponent.get());
}