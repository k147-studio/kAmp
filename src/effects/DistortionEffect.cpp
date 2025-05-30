#include "DistortionEffect.h"

// Lien de la doc : https://juce.com/tutorials/tutorial_dsp_convolution/

float DistortionEffect::currentRange = 0;

float DistortionEffect::clipWithCurrentRange(float x) {
    if (currentRange >= 1 || currentRange <= 0) {
        return juce::jlimit(-1.0f, 1.0f, x);
    }
    return juce::jlimit(-(1-currentRange), 1-currentRange, x);
}
/**
 * @brief Initializes a new instance of the DistortionEffect class.
 */
DistortionEffect::DistortionEffect() {
    currentRange = 0;
    effectName = "Distortion";
    auto &waveshaper = processorChain.template get<waveshaperIndex>();
    waveshaper.functionToUse = &clipWithCurrentRange;
}

/**
 * @brief Destroys the instance of the DistortionEffect class.
 */
DistortionEffect::~DistortionEffect() = default;



void DistortionEffect::prepare (const juce::dsp::ProcessSpec& spec)
{
    processorChain.prepare (spec);
}


void DistortionEffect::reset() noexcept
{
    processorChain.reset();
}

template <typename ProcessContext>
void DistortionEffect::process (const ProcessContext& context) noexcept
{
    processorChain.process (context);
}

void DistortionEffect::setRange(float rangeValue) {
    currentRange = rangeValue;
    auto& waveshaper = processorChain.template get<waveshaperIndex>();
    waveshaper.functionToUse = &clipWithCurrentRange;
}

float DistortionEffect::getRange() const {
    return currentRange;
}

/**
 * @brief Applies the distortion effect to the given audio buffer.
 * @param bufferToFill The audio buffer to apply the effect to.
 *
 * This implementation applies a simple hard-clipping distortion by multiplying
 * the input signal by the drive amount, then limiting it between -1.0 and 1.0.
 * Finally, it mixes the distorted (wet) signal with the original (dry) signal
 * according to the mix parameter.
 *
 * For a more advanced waveshaping approach, see:
 * https://docs.juce.com/master/structdsp_1_1WaveShaper.html
 */

void DistortionEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (bufferToFill.buffer == nullptr) return;

    juce::dsp::AudioBlock<float> block(*bufferToFill.buffer,
                                       (size_t) bufferToFill.startSample);
    auto subBlock = block.getSubBlock(0, (size_t) bufferToFill.numSamples);
    juce::dsp::ProcessContextReplacing<float> context(subBlock);
    subBlock.multiplyBy(1.0f / std::max(1.0f - currentRange, 0.01f)); // Normalisation du volume

    process(context);
}




/**
 * @brief Compares the effect with another given effect.
 * @param effect The effect to compare with.
 * @return True if the effect is equal to the given effect, false otherwise.
 */
bool DistortionEffect::operator==(const AbstractEffect *effect) {
    return dynamic_cast<const DistortionEffect *>(effect) != nullptr;
}

