#include "ReverbEffectComponent.h"

ReverbEffectComponent::ReverbEffectComponent()
    : BasePedalComponent(new ReverbEffect())
{
    primaryColor = juce::Colours::darkgreen;

    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    initializePedal();
}

ReverbEffectComponent::ReverbEffectComponent(AbstractEffect* effect)
    : BasePedalComponent(effect)
{
    if (auto* rev = dynamic_cast<ReverbEffect*>(effect))
    {
        primaryColor = juce::Colours::darkgreen;
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        initializePedal();
    }
    else
    {
        jassertfalse;
    }
}

ReverbEffectComponent::~ReverbEffectComponent() = default;
