#include "DistortionEffect.h"

// Lien de la doc : https://juce.com/tutorials/tutorial_dsp_convolution/

/**
 * @brief Initializes a new instance of the DistortionEffect class.
 */
DistortionEffect::DistortionEffect()
    : drive(1.0f), mix(1.0f)
{
    effectName = "Distortion";
    auto& sh = processorChain.get<waveshaperIndex>();
    sh.functionToUse = [this](float x)
    {
        return std::tanh(drive * x);
    };
}

/**
 * @brief Destroys the instance of the DistortionEffect class.
 */
DistortionEffect::~DistortionEffect() = default;



void DistortionEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    processorChain.prepare(spec);
    processorChain.reset();
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
void DistortionEffect::apply (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer      = bufferToFill.buffer;
    const auto start  = (size_t) bufferToFill.startSample;
    const auto length = (size_t) bufferToFill.numSamples;

    auto fullBlock = juce::dsp::AudioBlock<float>(*buffer, start);

    auto subBlock = fullBlock.getSubBlock (0, length);

    dsp::ProcessContextReplacing ctx (subBlock);
    processorChain.process (ctx);

    for (int ch = 0; ch < buffer->getNumChannels(); ++ch)
    {
        auto* write = buffer->getWritePointer (ch, bufferToFill.startSample);
        auto* read  = buffer->getReadPointer  (ch, bufferToFill.startSample);
        for (int i = 0; i < bufferToFill.numSamples; ++i)
            write[i] = read[i] * (1.0f - mix) + write[i] * mix;
    }
}


/**
 * @brief Sets the drive amount for the distortion effect.
 * @param driveValue The drive (gain) amount before clipping.
 */
void DistortionEffect::setDrive(float driveValue) {
    drive = driveValue;
    auto& sh = processorChain.get<waveshaperIndex>();
    sh.functionToUse = [this](float x)
    {
        return std::tanh(drive * x);
    };
}

/**
 * @brief Sets the mix (dry/wet) of the distortion effect.
 * @param mixValue The mix between dry and wet signal (0.0 = dry, 1.0 = wet).
 */
void DistortionEffect::setMix(float mixValue) {
    mix = juce::jlimit(0.0f, 1.0f, mixValue);
}

/**
 * @brief Compares the effect with another given effect.
 * @param effect The effect to compare with.
 * @return True if the effect is equal to the given effect, false otherwise.
 */
bool DistortionEffect::operator==(const AbstractEffect *effect) {
    if (auto other = dynamic_cast<const DistortionEffect *>(effect)) {
        return drive == other->drive && mix == other->mix;
    }
    return false;
}

