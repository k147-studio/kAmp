#include "ChromaticTunerComponent.h"
#include "AppFonts.h"

const std::vector<std::string> ChromaticTunerComponent::notesNames = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

ChromaticTunerComponent::ChromaticTunerComponent(TuningState& state)
    : tuningState(state)
{
    startTimerHz(30);
}

ChromaticTunerComponent::~ChromaticTunerComponent()
{
    stopTimer();
}

void ChromaticTunerComponent::paint(juce::Graphics& g)
{
    auto area = getLocalBounds();
    constexpr int numBars = 11;
    constexpr int barWidth = 20;
    constexpr int barHeight = 30;
    constexpr float textHeight = 50.0f;
    const int centerX = area.getCentreX();

    g.setColour(isInTune ? juce::Colours::green : juce::Colours::orange);
    g.setFont(AppFonts::bold(40.0f));
    g.drawText(currentNote, 0, getHeight() / 2 - static_cast<int>(textHeight),
               area.getWidth(), static_cast<int>(textHeight), juce::Justification::centred);

    const float normalizedCents = juce::jlimit(-50.0f, 50.0f, currentTuneCents);
    const int highlightIndex = static_cast<int>(std::round(normalizedCents / 10.0f)) + 5;

    for (int i = 0; i < numBars; ++i)
    {
        const int x = centerX + (i - 5) * barWidth;
        const int y = getHeight() / 2;
        const bool isActive = (i == highlightIndex);
        const juce::Colour color = isActive
                                       ? (isInTune ? juce::Colours::green : juce::Colours::orange)
                                       : juce::Colours::grey;

        g.setColour(color);
        g.fillRect(x, y, barWidth - 2, barHeight);
    }
}

void ChromaticTunerComponent::resized() {}

void ChromaticTunerComponent::timerCallback()
{
    const bool hasSignal = tuningState.hasSignal.load(std::memory_order_relaxed);
    if (!hasSignal)
    {
        currentNote = "No Signal";
        currentTuneCents = 0.0f;
        isInTune = false;
        repaint();
        return;
    }

    currentTuneCents = tuningState.cents.load(std::memory_order_relaxed);
    isInTune = tuningState.isInTune.load(std::memory_order_relaxed);
    currentNote = noteNameForMidi(tuningState.midiNote.load(std::memory_order_relaxed));
    repaint();
}

std::string ChromaticTunerComponent::noteNameForMidi(int midiNote)
{
    if (midiNote < 0)
        return "Unknown";
    return notesNames[static_cast<size_t>(midiNote) % notesNames.size()];
}
