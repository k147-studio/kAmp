#pragma once
#include "EffectComponent.h"
#include "PedalPowerIndicatorComponent.h"
#include "PedalSettingsLayoutComponent.h"

/**
 * @brief Base class for pedal components.
 * This class provides a common interface and functionality for all pedal components.
 */
class BasePedalComponent : public EffectComponent, public DragAndDropTarget
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

    /**
     * @brief Handles mouse down events.
     * @param event The mouse event that occurred.
     */
    void mouseDown(const juce::MouseEvent& event) override;

    /**
     *
     * @param dragSourceDetails The details of the drag source.
     * @return A boolean indicating whether the component is interested in the drag source.
     */
    bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override;

    /**
     * @brief Handles the drop of a component onto this pedal component.
     * @param dragSourceDetails The details of the drag source.
     */
    void itemDropped(const SourceDetails& dragSourceDetails) override;

protected:
    /**
     * @brief The default width of the component.
     */
    const float DEFAULT_WIDTH = 200.0f;

    /**
     * @brief The default height of the component.
     */
    const float DEFAULT_HEIGHT = 300.0f;

    /**
     * @brief The main layout for the pedal component.
     */
    juce::Grid pedalLayout;

    /**
     * @brief The primary color of the pedal component. Used as background color.
     */
    juce::Colour primaryColor;

    /**
    * @brief The secondary color of the pedal component. Used as background color.
    */
    juce::Colour secondaryColor;

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
