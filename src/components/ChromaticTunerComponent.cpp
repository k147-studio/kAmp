#include "ChromaticTunerComponent.h"

ChromaticTunerComponent::ChromaticTunerComponent(int sampleRate, int fftOrder)
    : notesNames({"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}),
      baseFrequency(440.0f), currentTuneCents(0), isInTune(false), currentNote("No Signal"), isTunerActive(false)
{
    tuner = new ChromaticTuner(fftOrder, sampleRate);
}

ChromaticTunerComponent::~ChromaticTunerComponent() = default;

void ChromaticTunerComponent::paint(juce::Graphics &g) {
    auto area = getLocalBounds();
    int numBars = 11;
    int barWidth = 20;
    int barHeight = 30;
    float textHeight = 50.0f;
    int centerX = area.getCentreX();

    // Drawing the note name.
    g.setColour(isInTune ? juce::Colours::green : juce::Colours::orange);
    g.setFont(40.0f);
    g.drawText(currentNote, 0, getHeight() / 2 - textHeight, area.getWidth(), textHeight, juce::Justification::centred);

    // Drawing the tuning bars.
    float normalizedCents = juce::jlimit(-50.0f, 50.0f, currentTuneCents);
    int highlightIndex = static_cast<int>(std::round(normalizedCents / 10.0f)) + 5;

    for (int i = 0; i < numBars; ++i) {
        int x = centerX + (i - 5) * barWidth;
        int y = getHeight() / 2;

        bool isActive = (i == highlightIndex);
        juce::Colour color = isActive ? (isInTune ? juce::Colours::green : juce::Colours::orange)
                                      : juce::Colours::grey;

        g.setColour(color);
        g.fillRect(x, y, barWidth - 2, barHeight);
    }
}

void ChromaticTunerComponent::resized() {
}

void ChromaticTunerComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
}

void ChromaticTunerComponent::tune(const AudioSourceChannelInfo &buffer) {
    if (!isTunerActive) {
        isTunerActive = true;
    }
    if (buffer.buffer == nullptr || buffer.buffer->getNumChannels() == 0) {
        return;
    }
    dsp::AudioBlock<float> audioBlock(*buffer.buffer);
    if (audioBlock.getNumSamples() == 0) {
        return;
    }
    dsp::AudioBlock<float> subBlock = audioBlock.getSingleChannelBlock((size_t)0);
    std::optional<float> frequency = tuner->getMainFrequencyFromAudioBlock(subBlock);
    if (frequency.has_value()) {
        float newFreq = frequency.value();
        if (smoothedFrequency == 0.0f)
            smoothedFrequency = newFreq;
        else
            smoothedFrequency = smoothingCoeff * newFreq + (1.0f - smoothingCoeff) * smoothedFrequency;
        ChromaticTuningResult result = detectTuning(frequency.value());
        updateTuningDisplay(result);
    } else {
        currentNote = "No Signal";
        currentTuneCents = 0.0f;
        isInTune = false;
        repaint();
    }
}

ChromaticTuningResult ChromaticTunerComponent::detectTuning(float frequency) {
    ChromaticTuningResult result;

    if (frequency <= 0.0f) return result;

    float midiFloat = 69 + 12 * std::log2(frequency / 440.0f);
    int midiNote = std::round(midiFloat);
    float exactFrequency = 440.0f * std::pow(2.0f, (midiNote - 69) / 12.0f);
    float deviation = 1200.0f * std::log2(frequency / exactFrequency);

    result.frequency = frequency;
    result.noteName = getNoteName(midiNote);
    result.deviation = deviation;
    result.isInTune = std::abs(deviation) < 5.0f;

    return result;
}

std::string ChromaticTunerComponent::getNoteName(int midiNote) {
    if (midiNote < 0) {
        return "Unknown";
    }
    return notesNames[midiNote % notesNames.size()];
}

void ChromaticTunerComponent::updateTuningDisplay(const ChromaticTuningResult& result) {
    if (result.frequency < 20.0f) {
        currentNote = "No Signal";
        currentTuneCents = 0.0f;
        isInTune = false;
    } else {
        currentNote = result.noteName;
        currentTuneCents = result.deviation; // Doit être l'écart en cents, pas la fréquence
        isInTune = result.isInTune;
    }
    repaint();
}

bool ChromaticTunerComponent::isTuning() {
    return isTunerActive;
}