#pragma once

#include <JuceHeader.h>

/**
 * @brief Represents a graphical component that indicates the power status of a pedal.
 */
class PedalPowerIndicatorComponent: public juce::Component
{
public:
    /**
     * @brief Initializes a new instance of the PedalPowerIndicatorComponent class.
     * @param isEnabled Indicates whether the pedal is enabled or not.
     */
    explicit PedalPowerIndicatorComponent(bool isEnabled = true);

    /**
     * @brief Destroys the instance of the PedalPowerIndicatorComponent class.
     */
    ~PedalPowerIndicatorComponent() override;

    /**
     * @brief Paints the component.
     * @param g The JUCE graphics context that paints the component.
     */
    void paint(juce::Graphics &g) override;

    /**
     * @brief Toggles the power status of the pedal.
     * @param isEnabled Indicates whether the pedal is enabled or not.
     */
    void togglePower(bool isEnabled);
private:
    /**
     * @brief Indicates whether the pedal is enabled or not.
     */
    bool isEnabled;
};