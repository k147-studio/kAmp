#include "MainComponent.h"
#include "SettingsComponent.h"
#include "ResourceManager.h"

MainComponent::MainComponent(const Manager &manager): pedalboardComponent(manager.getPedalboard()),
                                                      topMenuBarComponent(this->deviceManager, &isSoundMuted, &tuningFunction), manager(manager)
{
    setAudioChannels(2, 2);

    Image background = ResourceManager::loadImage("resources/images/background.png");
    if (background.isValid()) {
        backgroundImage.setImage(background);
        backgroundImage.setImagePlacement(juce::RectanglePlacement::stretchToFit);
        addAndMakeVisible(backgroundImage);
    } else {
        DBG("Erreur : image de fond introuvable ou invalide.");
    }

    pedalboardContainer.setViewedComponent(&pedalboardComponent, true);
    pedalboardContainer.setScrollBarsShown(true, false);

    addAndMakeVisible(pedalboardContainer);
    addAndMakeVisible(topMenuBarComponent);
    addAndMakeVisible(bottomMenuBarComponent);
    addAndMakeVisible(connectionComponent);
}

MainComponent::~MainComponent()
{
    releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    backgroundImage.setBounds(getLocalBounds());
    connectionComponent.setBounds(getLocalBounds());

    int pedalboardWidth = getWidth();
    int pedalboardHeight = pedalboardComponent.getRequiredHeight(getWidth());
    pedalboardComponent.setSize(pedalboardWidth, pedalboardHeight);

    using Track = juce::Grid::TrackInfo;
    using Px = juce::Grid::Px;
    using Fr = juce::Grid::Fr;
    grid.templateRows = { Track (Px (50)), Track (Fr(1)) };
    grid.templateColumns = { Track (Fr(1)) };
    grid.items = {
        juce::GridItem(topMenuBarComponent),
        juce::GridItem(pedalboardContainer)
    };
    grid.performLayout(getLocalBounds());
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {

}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) {
    if (!this->isSoundMuted)
    {
        if (&bufferToFill == nullptr) {
            return;
        }
        if (bufferToFill.buffer == nullptr) {
            return;
        }
        this->manager.apply(bufferToFill);
    }
    else
    {
        bufferToFill.clearActiveBufferRegion();
    }
    if (tuningFunction != nullptr) {
        tuningFunction(bufferToFill);
    }
}

void MainComponent::releaseResources() {
    shutdownAudio();
}


