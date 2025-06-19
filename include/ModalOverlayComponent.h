#pragma once
#include <JuceHeader.h>

class ModalOverlayComponent : public juce::Component
{
public:
    ModalOverlayComponent(std::string viewName, juce::Component* modalContent, std::function<void()> onCloseCallback);
    ~ModalOverlayComponent() override = default;
    void resized() override;
    void paint(Graphics& g) override;

private:
    juce::Label viewNameLabel;
    juce::ImageButton closeOverlayButton;
    juce::Component* modalComponent = nullptr;
    std::function<void()> onCloseCallback;

    void onCloseOverlayButtonClicked();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModalOverlayComponent)
};

