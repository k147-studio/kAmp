#pragma once

#include "EffectComponent.h"
#include "Manager.h"

#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

/**
 * @brief Displays the pedalboard and keeps UI order in sync with Manager mutations.
 */
class PedalboardComponent : public EffectComponent,
                            public DragAndDropContainer,
                            private ChangeListener
{
public:
    explicit PedalboardComponent(Manager& manager);
    ~PedalboardComponent() override;

    void addEffect(EffectComponent* effectComponent);
    void resized() override;
    void paint(Graphics& g) override;

    int getRequiredWidth() const;
    int getRequiredHeight(int boardWidth) const;

    void onPedalDropped(Component* target, Component* dragged);
    void onPedalDropped(EffectComponent* target, EffectComponent* dragged);

private:
    struct PreferredSize
    {
        int width = 0;
        int height = 0;
    };

    void changeListenerCallback(ChangeBroadcaster* source) override;
    void rebuildFromPedalboard();
    void refreshFlexBox();
    void clearEffectComponents();

    Manager& manager;
    const int PEDALS_MARGIN = 20;
    std::vector<Component*> effectsComponents;
    std::vector<PreferredSize> preferredSizes;
    FlexBox flexBox;
};
