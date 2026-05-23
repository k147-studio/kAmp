#include "ModalOverlayComponent.h"

#include "AppFonts.h"
#include "ResourceManager.h"

ModalOverlayComponent::ModalOverlayComponent(std::string viewName,
                                             juce::Component* modalContent,
                                             std::function<void()> closeCallback)
	: modalComponent(modalContent),
	  onCloseCallback(std::move(closeCallback))
{
	setInterceptsMouseClicks(true, true);

	if (modalComponent != nullptr)
	{
		modalComponent->setInterceptsMouseClicks(true, true);
		addAndMakeVisible(modalComponent);
	}

	addAndMakeVisible(viewNameLabel);
	viewNameLabel.setText(viewName, juce::dontSendNotification);
	viewNameLabel.setFont(AppFonts::bold(32.0f));
	viewNameLabel.setJustificationType(juce::Justification::centred);
	viewNameLabel.setColour(juce::Label::textColourId, juce::Colours::white);

	ResourceManager::configureIconButton(closeOverlayButton, ResourceManager::getCloseIcon());
	closeOverlayButton.onClick = [this] { requestClose(); };
	addAndMakeVisible(closeOverlayButton);
}

void ModalOverlayComponent::resized()
{
	constexpr int headerHeight = 50;
	constexpr int closeButtonSize = 32;

	viewNameLabel.setBounds(0, 0, getWidth(), headerHeight);
	closeOverlayButton.setBounds(getWidth() - closeButtonSize - 16, (headerHeight - closeButtonSize) / 2,
	                             closeButtonSize, closeButtonSize);

	if (modalComponent != nullptr)
		modalComponent->setBounds(getLocalBounds().withTrimmedTop(headerHeight));

	// Keep chrome above content so the close button stays clickable.
	viewNameLabel.toFront(false);
	closeOverlayButton.toFront(false);
}

void ModalOverlayComponent::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::black.withAlpha(0.8f));
}

void ModalOverlayComponent::requestClose()
{
	// Defer so we are not destroyed mid-click while still on the call stack.
	auto callback = std::move(onCloseCallback);
	juce::MessageManager::callAsync([cb = std::move(callback)] {
		if (cb != nullptr)
			cb();
	});
}
