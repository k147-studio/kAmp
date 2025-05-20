#pragma once
#include "EffectComponent.h"
#include "PedalSettingsLayoutComponent.h"

class BasePedalComponent : public EffectComponent
{
public:
    BasePedalComponent(AbstractEffect* effect);
    ~BasePedalComponent() override;
    void paint(juce::Graphics &g) override;
    void resized() override;
protected:
    juce::Grid pedalLayout;
    PedalSettingsLayoutComponent* settingsLayout;
    juce::Label* pedalLabel;
    juce::Button* enablePedalButton;
    bool* isEnabled;
    void onEnableButtonClicked();
};
