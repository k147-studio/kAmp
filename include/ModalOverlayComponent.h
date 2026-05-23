#pragma once
#include <JuceHeader.h>
#include <functional>
#include <string>

class ModalOverlayComponent : public juce::Component
{
public:
	ModalOverlayComponent(std::string viewName, Component* modalContent,
	                      std::function<void()> onCloseCallback);
	~ModalOverlayComponent() override = default;

	void resized() override;
	void paint(Graphics& g) override;

private:
	juce::Label viewNameLabel;
	DrawableButton closeOverlayButton { "close", DrawableButton::ImageFitted };
	juce::Component* modalComponent = nullptr;
	std::function<void()> onCloseCallback;

	void requestClose();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModalOverlayComponent)
};
