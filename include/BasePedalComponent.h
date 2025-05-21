#pragma once
#include "EffectComponent.h"
#include "PedalPowerIndicatorComponent.h"
#include "PedalSettingsLayoutComponent.h"

/**
 * @brief Base class for pedal components.
 * This class provides a common interface and functionality for all pedal components.
 */
class BasePedalComponent : public EffectComponent
{
public:
    /**
     * @brief Initializes a new instance of the BasePedalComponent class.
     * @param effect The effect associated with this pedal component.
     */
    BasePedalComponent(AbstractEffect* effect);

    /**
     * @brief Destroys the instance of the BasePedalComponent class.
     */
    ~BasePedalComponent() override;

    /**
     * @brief Paints the component.
     * @param g The JUCE graphics context that paints the component.
     */
    void paint(juce::Graphics &g) override;

    /**
     * @brief Resizes the component.
     */
    void resized() override;
protected:
    /**
     * @brief The main layout for the pedal component.
     */
    juce::Grid pedalLayout;

    /**
     * @brief The primary color of the pedal component. Used as background color.
     */
    juce::Colour primaryColor;

    /**
     * @brief The layout for the pedal settings.
     */
    PedalSettingsLayoutComponent* settingsLayout;

    /**
     * @brief The label for the pedal name.
     */
    juce::Label* pedalLabel;

    /**
     * @brief The button to enable/disable the pedal.
     */
    juce::ImageButton enablePedalButton;

    /**
     * @brief The indicator for the pedal power status.
     */
    PedalPowerIndicatorComponent* isEnabledIndicator;

    /**
     * @brief Tells if the pedal is enabled or not.
     */
    bool* isEnabled;

    /**
     * @brief Called when the enable button is clicked.
     */
    void onEnableButtonClicked();

    /**
     * @brief Initializes the pedal layout to display it.
     */
    void initializePedal();
};
