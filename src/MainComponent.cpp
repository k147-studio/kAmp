#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (900, 700);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll ( juce::Colours::black);
    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello kAmp!", getLocalBounds(), juce::Justification::centred, true);

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
