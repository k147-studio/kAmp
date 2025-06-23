#include "ChorusEffect.h"

ChorusEffect::ChorusEffect() {
    effectName = "Chorus";
    updateParameters();
}

void ChorusEffect::apply(const juce::AudioSourceChannelInfo& bufferToFill) {
    auto* buffer = bufferToFill.buffer;
    if (buffer == nullptr || buffer->getNumSamples() == 0 || buffer->getNumChannels() == 0)
        return;

    juce::dsp::AudioBlock<float> block(*buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    chorus.process(context);
}


void ChorusEffect::updateParameters() {
    chorus.setRate(rate);
    chorus.setDepth(depth);
    chorus.setCentreDelay(centreDelay);
    chorus.setFeedback(feedback);
    chorus.setMix(mix);
}

float ChorusEffect::getDepth() const { return depth; }
float ChorusEffect::getRate() const { return rate; }
float ChorusEffect::getMix() const { return mix; }

void ChorusEffect::setRate(float newRate) {
    rate = newRate;
    chorus.setRate(rate);
}

void ChorusEffect::setDepth(float newDepth) {
    depth = newDepth;
    chorus.setDepth(depth);
}

void ChorusEffect::setCentreDelay(float newCentreDelay) {
    centreDelay = newCentreDelay;
    chorus.setCentreDelay(centreDelay);
}

void ChorusEffect::setFeedback(float newFeedback) {
    feedback = newFeedback;
    chorus.setFeedback(feedback);
}

void ChorusEffect::setMix(float newMix) {
    mix = newMix;
    chorus.setMix(mix);
}

void ChorusEffect::prepare(const juce::dsp::ProcessSpec& spec)
{
    chorus.prepare(spec);
}


bool ChorusEffect::operator==(const AbstractEffect* effect) {
    return this == effect;
}

juce::var ChorusEffect::toJSON() const {
    auto obj = AbstractEffect::toJSON();
    if (auto* dynamicObj = obj.getDynamicObject()) {
        dynamicObj->setProperty("rate", rate);
        dynamicObj->setProperty("depth", depth);
        dynamicObj->setProperty("centreDelay", centreDelay);
        dynamicObj->setProperty("feedback", feedback);
        dynamicObj->setProperty("mix", mix);
    }
    return obj;
}

void ChorusEffect::fromJSON(const juce::var& json) {
    AbstractEffect::fromJSON(json);
    if (const auto* obj = json.getDynamicObject()) {
        if (obj->hasProperty("rate")) setRate((float)obj->getProperty("rate"));
        if (obj->hasProperty("depth")) setDepth((float)obj->getProperty("depth"));
        if (obj->hasProperty("centreDelay")) setCentreDelay((float)obj->getProperty("centreDelay"));
        if (obj->hasProperty("feedback")) setFeedback((float)obj->getProperty("feedback"));
        if (obj->hasProperty("mix")) setMix((float)obj->getProperty("mix"));
    }
}
