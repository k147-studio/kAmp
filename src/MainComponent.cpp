#include "MainComponent.h"
#include "SettingsComponent.h"

MainComponent::MainComponent(const Manager &manager): pedalboardComponent(manager.getPedalboard()),
                                                      topMenuBarComponent(this->deviceManager, &isSoundMuted), manager(manager)
{
    setAudioChannels(2, 2);
    Image background = ImageFileFormat::loadFrom(File(File::getCurrentWorkingDirectory().getChildFile("resources/images/background.png")));
    backgroundImage.setImage(background);
    backgroundImage.setImagePlacement(RectanglePlacement(RectanglePlacement::stretchToFit));

    addAndMakeVisible(backgroundImage);
    addAndMakeVisible(pedalboardComponent);
    addAndMakeVisible(topMenuBarComponent);
    addAndMakeVisible(bottomMenuBarComponent);
    addAndMakeVisible(connectionComponent);
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
    using Track = juce::Grid::TrackInfo;
    using Px = juce::Grid::Px;
    using Fr = juce::Grid::Fr;
    grid.templateRows = { Track (Px (50)), Track (Px(getHeight() - 150)) };
    grid.templateColumns = { Track (Fr(1)) };
    grid.items = {
        juce::GridItem(topMenuBarComponent),
        juce::GridItem(pedalboardComponent)
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
}

void MainComponent::releaseResources() {
}


