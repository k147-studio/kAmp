#pragma once
#include <JuceHeader.h>

class ModalOverlayComponent final : public Component {
public:
	ModalOverlayComponent(std::string viewName, Component* modalContent,
	                      std::function<void()> onCloseCallback);
	~ModalOverlayComponent() override = default;
	void resized() override;
	void paint(Graphics& g) override;

private:
	Label viewNameLabel;
	ImageButton closeOverlayButton;
	Component* modalComponent = nullptr;
	std::function<void()> onCloseCallback;

	void onCloseOverlayButtonClicked();
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModalOverlayComponent)
};

