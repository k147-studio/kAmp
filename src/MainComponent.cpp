#include "MainComponent.h"
#include "SettingsComponent.h"

//==============================================================================
MainComponent::MainComponent(Manager manager): pedalboardComponent(manager.getPedalboard()), manager(manager) {
    setAudioChannels(2, 2);
    setSize(900, 700);
    addAndMakeVisible(pedalboardComponent);
    addAndMakeVisible(topMenuBarComponent);
    addAndMakeVisible(bottomMenuBarComponent);
    addAndMakeVisible(connectionComponent);

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::grey);

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    connectionComponent.setBounds(getLocalBounds());
    using Track = juce::Grid::TrackInfo;
    using Px = juce::Grid::Px;
    using Fr = juce::Grid::Fr;
    grid.templateRows = { Track (Px (50)), Track (Px(getHeight() - 150)), Track (Px (100)) };
    grid.templateColumns = { Track (Fr(1)) };
    grid.items = {
        juce::GridItem(topMenuBarComponent),
        juce::GridItem(pedalboardComponent),
        juce::GridItem(bottomMenuBarComponent)
    };
    grid.performLayout(getLocalBounds());
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    if (bufferToFill.buffer == nullptr) {
        return;
    }
    this->manager.apply(bufferToFill);
}

void MainComponent::releaseResources() {
}


