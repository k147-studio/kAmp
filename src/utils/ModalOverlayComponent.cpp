#include "ModalOverlayComponent.h"

#include "ResourceManager.h"

ModalOverlayComponent::ModalOverlayComponent(std::string viewName, juce::Component* modalContent)
{
    addAndMakeVisible(modalComponent = modalContent);
    this->setInterceptsMouseClicks(true, false);

    modalComponent->setInterceptsMouseClicks(true, true);
    modalComponent->setCentreRelative(0.5f, 0.5f);

    addAndMakeVisible(viewNameLabel);
    viewNameLabel.setText(viewName, juce::dontSendNotification);
    viewNameLabel.setFont(juce::FontOptions(32.0f, juce::Font::bold));
    viewNameLabel.setJustificationType(juce::Justification::centred);

    juce::Image closeImage = ResourceManager::loadImage("resources/icons/close.png");
    if (closeImage.isValid()) {
        closeOverlayButton.setImages(true, true, true,closeImage, 1.0f, {}, closeImage, 1.0f, {},closeImage, 1.0f, {});
        closeOverlayButton.setSize(closeImage.getWidth(), closeImage.getHeight());
        addAndMakeVisible(closeOverlayButton);
    } else {
        DBG("Erreur : image close.png introuvable ou invalide.");
    }
    closeOverlayButton.onClick = [this]() { this->onCloseOverlayButtonClicked(); };
}

void ModalOverlayComponent::resized()
{
    viewNameLabel.setBounds(0, 0, getWidth(), 50);
    closeOverlayButton.setBounds(getWidth() - 100, 10, 100, 50);
    if (modalComponent != nullptr)
    {
        modalComponent->setBounds(getLocalBounds());
    }
}

void ModalOverlayComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.withAlpha(0.8f));
}

void ModalOverlayComponent::onCloseOverlayButtonClicked()
{
    if (modalComponent != nullptr)
    {
        removeAllChildren();
        auto* mainWindow = getTopLevelComponent();
        if (mainWindow == nullptr)
            return;
        mainWindow->removeChildComponent(this);
    }
}