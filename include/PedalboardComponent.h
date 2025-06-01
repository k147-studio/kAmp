#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "Pedalboard.h"
#include "EffectComponent.h"

/**
 * @brief Represents a graphical component that contains and displays a pedalboard.
 */
class PedalboardComponent : public EffectComponent {
  public:
    /**
     * @brief Initializes a new instance of the PedalboardComponent class.
     * @param pedalboard The pedalboard to initialize the component with.
     */
    PedalboardComponent(AbstractEffect* pedalboard);

    /**
     * @brief Destroys the instance of the PedalboardComponent class.
     */
    ~PedalboardComponent() override;

    /**
     * @brief Adds an EffectComponent to the pedalboard.
     * @param effect The EffectComponent to add to the pedalboard.
     */
    void addEffect(EffectComponent* effect);

    /**
     * @brief Determines what to do when the component is resized.
     */
    void resized() override;

    /**
     * @brief Determines how the component is displayed.
     * @param g The JUCE graphics context that paints the component.
     */
    void paint(juce::Graphics &g) override;

    /**
     * @brief Gets the required width for the pedalboard based on its effects.
     * @return The required width for the pedalboard.
     */
    int getRequiredWidth() const;

    /**
     * @brief Gets the required height for the pedalboard based on its effects.
     * @return The required height for the pedalboard.
     */
    int getRequiredHeight(const int boardWidth) const;
  private:

    /**
     * @brief The default margin between pedals.
     */
    const int PEDALS_MARGIN = 20;

    /**
     * @brief The collection of the effect components in the pedalboard.
     */
    std::vector<juce::Component*> effectsComponents;

    /**
     * @brief The flexbox that arranges layout for the effect components in the pedalboard.
     */
    juce::FlexBox flexBox;
};