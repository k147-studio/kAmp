#include "AccountComponent.h"

AccountComponent::AccountComponent()
{
    // Ajoute ici les éléments de compte si nécessaire
}

void AccountComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightblue);
    g.setColour(juce::Colours::black);
    g.drawText("Account", getLocalBounds(), juce::Justification::centred, true);
}

void AccountComponent::resized()
{
    // À compléter si tu ajoutes des éléments internes
}

