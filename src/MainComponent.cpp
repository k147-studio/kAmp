#include "MainComponent.h"

MainComponent::MainComponent(std::unique_ptr<Pedalboard> pedalboard)
    : audioEngine(std::move(pedalboard)),
      manager(audioEngine.getPedalboard()),
      pedalboardComponent(manager),
      topMenuBarComponent(deviceManager,
                          &audioEngine.getMuteFlag(),
                          &audioEngine.getTuningState())
{
    setAudioChannels(2, 2);

    // Member component — do not let Viewport take ownership.
    pedalboardContainer.setViewedComponent(&pedalboardComponent, false);
    pedalboardContainer.setScrollBarsShown(false, true);

    addAndMakeVisible(pedalboardContainer);
    addAndMakeVisible(topMenuBarComponent);
    addAndMakeVisible(bottomMenuBarComponent);
}

MainComponent::~MainComponent()
{
    audioEngine.getTuningState().enabled.store(false, std::memory_order_release);
    topMenuBarComponent.closeAllModals();
    shutdownAudio();
}

void MainComponent::paint(Graphics& g)
{
    const ColourGradient gradient(Colour(0xff7c6c61), 0.0f, 0.0f,
                                  Colour(0xff1a191e), static_cast<float>(getWidth()),
                                  static_cast<float>(getHeight()), true);
    g.setGradientFill(gradient);
    g.fillAll();
}

void MainComponent::resized()
{
    constexpr int topBarHeight = 50;
    auto contentBounds = getLocalBounds();
    contentBounds.removeFromTop(topBarHeight);

    const int pedalboardWidth = juce::jmax(contentBounds.getWidth(),
                                           pedalboardComponent.getRequiredWidth());
    const int pedalboardHeight = contentBounds.getHeight();
    pedalboardComponent.setSize(pedalboardWidth, pedalboardHeight);

    pedalboardContainer.setBounds(contentBounds);
    topMenuBarComponent.setBounds(0, 0, getWidth(), topBarHeight);
    topMenuBarComponent.toFront(false);
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlockExpected);
    spec.numChannels = 2;
    audioEngine.prepare(spec);
}

void MainComponent::releaseResources()
{
    audioEngine.reset();
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    audioEngine.process(bufferToFill);
}
