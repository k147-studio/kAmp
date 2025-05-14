#include <JuceHeader.h>
#include "AccountComponent.h"
#include "ApiClient.h"

AccountComponent::AccountComponent() {
    addAndMakeVisible(responseLabel);

    responseLabel.setFont(Font(FontOptions(20.0f, Font::bold)));
    responseLabel.setJustificationType(Justification::centred);
    responseLabel.setColour(Label::textColourId, Colours::black);
    responseLabel.setText("Waiting for API response...", dontSendNotification);

    auto replyFunc = [this](const String &content) {
        apiResponseReceived(content);
    };

    ApiClient::runHTTP({"https://dummyjson.com/test"}, replyFunc);
}

void AccountComponent::paint(Graphics &g) {
    g.fillAll(Colours::lightblue);
    g.setColour(Colours::black);
    g.setFont(Font(FontOptions(20.0f, Font::bold)));
    g.drawText("Account", getLocalBounds().removeFromTop(40), Justification::centred, true);
}

void AccountComponent::apiResponseReceived(const String& content) {
    responseLabel.setText(content, dontSendNotification);
}

void AccountComponent::resized() {
    auto bounds = getLocalBounds();
    bounds.removeFromTop(50);
    responseLabel.setBounds(bounds.reduced(20));
}