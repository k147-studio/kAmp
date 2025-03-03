#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(): pedalboardComponent(manager.getPedalboard()), connectionComponent() {
    setSize(900, 700);
    addAndMakeVisible(pedalboardComponent);
    addAndMakeVisible(connectionComponent);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll(juce::Colours::grey);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {

}

void MainComponent::releaseResources() {

}


