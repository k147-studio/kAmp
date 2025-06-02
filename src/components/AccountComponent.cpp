#include <JuceHeader.h>
#include "AccountComponent.h"
#include "ApiClient.h"

AccountComponent::AccountComponent() {
    addAndMakeVisible(responseLabel);

    responseLabel.setFont(Font(FontOptions(20.0f, Font::bold)));
    responseLabel.setJustificationType(Justification::centred);
    responseLabel.setColour(Label::textColourId, Colours::white);
    responseLabel.setText("Waiting for API response...", dontSendNotification);

    auto replyFunc = [this](const String &content) {
        apiResponseReceived(content);
    };

    ApiClient::runHTTP({"https://dummyjson.com/test"}, replyFunc);
}

void AccountComponent::paint(Graphics &g) {
}

void AccountComponent::apiResponseReceived(const String& content) {
    responseLabel.setText(content, dontSendNotification);
}

void AccountComponent::resized() {
    responseLabel.setBounds(getLocalBounds().reduced(20));
}