#include "ChorusEffect.h"

ChorusEffect::ChorusEffect() {
    effectName = "Chorus";
}

void ChorusEffect::syncParameters() {
    chorus.setRate(rate.load(std::memory_order_relaxed));
    chorus.setDepth(depth.load(std::memory_order_relaxed));
    chorus.setCentreDelay(centreDelay.load(std::memory_order_relaxed));
    chorus.setFeedback(feedback.load(std::memory_order_relaxed));
    chorus.setMix(mix.load(std::memory_order_relaxed));
}

void ChorusEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill) {
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || buffer->getNumSamples() == 0 || buffer->getNumChannels() == 0)
        return;

    syncParameters();

    juce::dsp::AudioBlock<float> block(*buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    chorus.process(context);
}

float ChorusEffect::getDepth() const { return depth.load(std::memory_order_relaxed); }
float ChorusEffect::getRate() const { return rate.load(std::memory_order_relaxed); }
float ChorusEffect::getMix() const { return mix.load(std::memory_order_relaxed); }

void ChorusEffect::setRate(float newRate) {
    rate.store(newRate, std::memory_order_relaxed);
}

void ChorusEffect::setDepth(float newDepth) {
    depth.store(newDepth, std::memory_order_relaxed);
}

void ChorusEffect::setCentreDelay(float newCentreDelay) {
    centreDelay.store(newCentreDelay, std::memory_order_relaxed);
}

void ChorusEffect::setFeedback(float newFeedback) {
    feedback.store(newFeedback, std::memory_order_relaxed);
}

void ChorusEffect::setMix(float newMix) {
    mix.store(newMix, std::memory_order_relaxed);
}

void ChorusEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    chorus.prepare(spec);
    syncParameters();
}

void ChorusEffect::reset()
{
    chorus.reset();
}

bool ChorusEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}

juce::var ChorusEffect::toJSON() const {
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject()) {
        dynamicObj->setProperty("rate", getRate());
        dynamicObj->setProperty("depth", getDepth());
        dynamicObj->setProperty("centreDelay", centreDelay.load(std::memory_order_relaxed));
        dynamicObj->setProperty("feedback", feedback.load(std::memory_order_relaxed));
        dynamicObj->setProperty("mix", getMix());
    }
    return obj;
}

void ChorusEffect::fromJSON(const juce::var& json) {
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject()) {
        if (obj->hasProperty("rate"))        setRate((float)obj->getProperty("rate"));
        if (obj->hasProperty("depth"))       setDepth((float)obj->getProperty("depth"));
        if (obj->hasProperty("centreDelay")) setCentreDelay((float)obj->getProperty("centreDelay"));
        if (obj->hasProperty("feedback"))    setFeedback((float)obj->getProperty("feedback"));
        if (obj->hasProperty("mix"))         setMix((float)obj->getProperty("mix"));
    }
}
