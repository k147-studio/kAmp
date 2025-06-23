#include "AccountComponent.h"
#include "ApiClient.h"

namespace {
constexpr float titleFontSize = 24.0f;
constexpr float labelFontSize = 16.0f;
constexpr float responseFontSize = 14.0f;
}

AccountComponent::AccountComponent() {
	setupLabels();
	setupButtons();
	setupGrid();

	// Dummy API call
	auto replyFunc = [this](const String& content) {
		apiResponseReceived(content);
	};
	ApiClient::runHTTP({"https://dummyjson.com/test"}, replyFunc);
}

void AccountComponent::setupLabels() {
	titleLabel.setFont(FontOptions(titleFontSize, Font::bold));
	titleLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(titleLabel);

	for (auto* label : {&emailLabel, &usernameLabel}) {
		label->setFont(FontOptions(labelFontSize));
		label->setJustificationType(Justification::centredLeft);
		addAndMakeVisible(*label);
	}

	for (auto* val : {&emailValueLabel, &usernameValueLabel}) {
		val->setFont(FontOptions(labelFontSize));
		val->setJustificationType(Justification::centredLeft);
		val->setColour(Label::textColourId, Colours::black);
		addAndMakeVisible(*val);
	}

	responseLabel.setFont(FontOptions(responseFontSize));
	responseLabel.setJustificationType(Justification::centred);
	responseLabel.setColour(Label::textColourId, Colours::darkgrey);
	addAndMakeVisible(responseLabel);
}

void AccountComponent::setupButtons() {
	saveButton.onClick = [this] { saveSettings(); };
	importButton.onClick = [this] { importSettings(); };

	for (auto* button : {&saveButton, &importButton})
		addAndMakeVisible(*button);
}

void AccountComponent::setupGrid() {
	using namespace juce;
	grid.templateRows = {
		Grid::TrackInfo(40_px), // Title
		Grid::TrackInfo(30_px), // Email label
		Grid::TrackInfo(30_px), // Email value
		Grid::TrackInfo(30_px), // Username label
		Grid::TrackInfo(30_px), // Username value
		Grid::TrackInfo(20_px), // Spacer
		Grid::TrackInfo(40_px), // Change password button
		Grid::TrackInfo(40_px), // Save button
		Grid::TrackInfo(40_px), // Import button
		Grid::TrackInfo(30_px) // Response label
	};

	grid.templateColumns = {Grid::TrackInfo(1_fr)};

	grid.items = {
		GridItem(titleLabel),
		GridItem(emailLabel),
		GridItem(emailValueLabel),
		GridItem(usernameLabel),
		GridItem(usernameValueLabel),
		GridItem().withArea(6, 1), // Spacer
		GridItem(saveButton),
		GridItem(importButton),
		GridItem(responseLabel)
	};
}

void AccountComponent::paint(Graphics& g) {
	g.fillAll(Colours::lightgrey);
}

void AccountComponent::resized() {
	grid.performLayout(getLocalBounds().reduced(40));
}

void AccountComponent::apiResponseReceived(const String& content) {
	responseLabel.setText("Réponse API : " + content, dontSendNotification);
}

void AccountComponent::saveSettings() {
	responseLabel.setText("✅ Réglages sauvegardés !", dontSendNotification);
}

void AccountComponent::importSettings() {
	emailValueLabel.setText("import@example.com", dontSendNotification);
	usernameValueLabel.setText("UtilisateurImporté", dontSendNotification);
	responseLabel.setText("📥 Réglages importés", dontSendNotification);
}
