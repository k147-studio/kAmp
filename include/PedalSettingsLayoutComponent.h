#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class PedalSettingsLayoutComponent: public juce::Component
{
public:
    PedalSettingsLayoutComponent(juce::Grid* layout);
    ~PedalSettingsLayoutComponent() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
private:
    juce::Grid* layout;
};
