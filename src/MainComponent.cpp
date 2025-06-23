#include "MainComponent.h"
#include "SettingsComponent.h"
#include "ResourceManager.h"

MainComponent::MainComponent(const Manager &manager):
    pedalboardComponent(manager.getPedalboard()),
    topMenuBarComponent(this->deviceManager, &isSoundMuted, &tuningFunction),
    manager(manager) {
    setAudioChannels(2, 2);

	const Image background = ResourceManager::loadImage(
		"resources/images/background.png");
	if (background.isValid()) {
		backgroundImage.setImage(background);
		backgroundImage.setImagePlacement(RectanglePlacement::stretchToFit);
		addAndMakeVisible(backgroundImage);
	} else {
		DBG("Error : resources/images/background.png not found.");
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
                                  double sampleRate) {
	juce::dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = (juce::uint32) samplesPerBlockExpected;
	auto* device = deviceManager.getCurrentAudioDevice();
	spec.numChannels = static_cast<juce::uint32>(
		device->getActiveOutputChannels().countNumberOfSetBits()
	);
	manager.prepare(spec);
}

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
	if (tuningFunction != nullptr) {
		tuningFunction(bufferToFill);
	}
}

void MainComponent::releaseResources() {
    shutdownAudio();
}


