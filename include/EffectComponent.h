#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "AbstractEffect.h"

/**
 * @brief Abstract class that represents what an effect component should have.
 */
class EffectComponent : public juce::Component
{
    public:
        /**
         * @brief Gets the AbstractEffect instance of the component.
         * @return The AbstractEffect instance of the component.
         */
        AbstractEffect* getEffect();
    protected:
        /**
         * @brief Initializes a new instance of the EffectComponent class.
         * @param effect The effect to initialize the component with.
         */
        explicit EffectComponent(AbstractEffect* effect);

        /**
         * @brief Destroys the instance of the EffectComponent class.
         */
        ~EffectComponent() override = default;

        /**
         * @brief The effect that the component represents.
         */
        AbstractEffect* effect;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectComponent)
};