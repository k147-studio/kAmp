#include "MainComponent.h"
#include "ResourceManager.h"
#include "BinaryData.h"



MainComponent::MainComponent(const Manager& manager):
	pedalboardComponent(manager.getPedalboard()),
	topMenuBarComponent(this->deviceManager, &isSoundMuted), manager(manager) {
	setAudioChannels(2, 2);


	juce::Image img = juce::ImageFileFormat::loadFrom(BinaryData::background_png, BinaryData::background_pngSize);
	backgroundImage.setImage(img);

	pedalboardContainer.setViewedComponent(&pedalboardComponent, true);
	pedalboardContainer.setScrollBarsShown(true, false);

	addAndMakeVisible(backgroundImage);
	addAndMakeVisible(pedalboardContainer);
	addAndMakeVisible(topMenuBarComponent);
	addAndMakeVisible(bottomMenuBarComponent);
	addAndMakeVisible(connectionComponent);
}

//==============================================================================
void MainComponent::paint(Graphics& g) {}

void MainComponent::resized() {
	backgroundImage.setBounds(getLocalBounds());
	connectionComponent.setBounds(getLocalBounds());

	int pedalboardWidth = getWidth();
	int pedalboardHeight = pedalboardComponent.getRequiredHeight(getWidth());
	pedalboardComponent.setSize(pedalboardWidth, pedalboardHeight);

	using Track = Grid::TrackInfo;
	using Px = Grid::Px;
	using Fr = Grid::Fr;
	grid.templateRows = {Track(Px(50)), Track(Fr(1))};
	grid.templateColumns = {Track(Fr(1))};
	grid.items = {
		GridItem(topMenuBarComponent),
		GridItem(pedalboardContainer)
	};
	grid.performLayout(getLocalBounds());
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected,
                                  double sampleRate) {}

void MainComponent::getNextAudioBlock(
	const AudioSourceChannelInfo& bufferToFill) {
	if (!this->isSoundMuted) {
		if (&bufferToFill == nullptr) {
			return;
		}
		if (bufferToFill.buffer == nullptr) {
			return;
		}
		this->manager.apply(bufferToFill);
	} else {
		bufferToFill.clearActiveBufferRegion();
	}
}

void MainComponent::releaseResources() {}


