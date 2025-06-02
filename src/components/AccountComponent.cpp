#include "AccountComponent.h"
#include "ApiClient.h"

AccountComponent::AccountComponent()
{
    // --- Titre ---
    titleLabel.setText("Mon compte", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    // --- Labels de champs ---
    emailLabel.setText("Adresse mail :", juce::dontSendNotification);
    usernameLabel.setText("Nom d'utilisateur :", juce::dontSendNotification);

    for (auto* label : { &emailLabel, &usernameLabel })
    {
        label->setFont(juce::Font(16.0f));
        label->setJustificationType(juce::Justification::centredLeft);
        addAndMakeVisible(*label);
    }

    // --- Valeurs (non éditables) ---
    emailValueLabel.setText("utilisateur@example.com", juce::dontSendNotification);
    usernameValueLabel.setText("NomUtilisateur", juce::dontSendNotification);

    for (auto* val : { &emailValueLabel, &usernameValueLabel })
    {
        val->setFont(juce::Font(16.0f));
        val->setJustificationType(juce::Justification::centredLeft);
        val->setColour(juce::Label::textColourId, juce::Colours::black);
        addAndMakeVisible(*val);
    }

    // --- Boutons ---
    saveButton.setButtonText("Sauvegarder les réglages");
    importButton.setButtonText("Importer les réglages");
    changePasswordButton.setButtonText("Changer le mot de passe");

    saveButton.onClick = [this]() { saveSettings(); };
    importButton.onClick = [this]() { importSettings(); };
    changePasswordButton.onClick = [this]() { changePassword(); };

    for (auto* button : { &saveButton, &importButton, &changePasswordButton })
        addAndMakeVisible(*button);

    // --- Label de réponse (API ou autres actions) ---
    responseLabel.setFont(juce::Font(14.0f));
    responseLabel.setJustificationType(juce::Justification::centred);
    responseLabel.setColour(juce::Label::textColourId, juce::Colours::darkgrey);
    responseLabel.setText("En attente de réponse...", juce::dontSendNotification);
    addAndMakeVisible(responseLabel);

    // --- Appel API fictif ---
    auto replyFunc = [this](const juce::String& content) {
        apiResponseReceived(content);
    };
    ApiClient::runHTTP({ "https://dummyjson.com/test" }, replyFunc);
}

void AccountComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void AccountComponent::resized()
{
    using namespace juce;

    grid.templateRows = {
        Grid::TrackInfo(40_px),  // Titre
        Grid::TrackInfo(30_px),  // Label email
        Grid::TrackInfo(30_px),  // Valeur email
        Grid::TrackInfo(30_px),  // Label username
        Grid::TrackInfo(30_px),  // Valeur username
        Grid::TrackInfo(20_px),
        Grid::TrackInfo(40_px),  // Bouton changer mdp
        Grid::TrackInfo(40_px),  // Bouton sauvegarder
        Grid::TrackInfo(40_px),  // Bouton importer
        Grid::TrackInfo(30_px)   // Label réponse
    };

    grid.templateColumns = { Grid::TrackInfo(1_fr) };

    grid.items = {
        GridItem(titleLabel),
        GridItem(emailLabel),
        GridItem(emailValueLabel),
        GridItem(usernameLabel),
        GridItem(usernameValueLabel),
        GridItem().withArea(6, 1), // espacement
        GridItem(changePasswordButton),
        GridItem(saveButton),
        GridItem(importButton),
        GridItem(responseLabel)
    };

    grid.performLayout(getLocalBounds().reduced(40));
}

void AccountComponent::apiResponseReceived(const juce::String& content)
{
    responseLabel.setText("Réponse API : " + content, juce::dontSendNotification);
}

void AccountComponent::saveSettings()
{
    responseLabel.setText("✅ Réglages sauvegardés !", juce::dontSendNotification);
}

void AccountComponent::importSettings()
{
    emailValueLabel.setText("import@example.com", juce::dontSendNotification);
    usernameValueLabel.setText("UtilisateurImporté", juce::dontSendNotification);
    responseLabel.setText("📥 Réglages importés", juce::dontSendNotification);
}

void AccountComponent::changePassword()
{
    // Action fictive pour changer le mot de passe
    responseLabel.setText("🔐 Redirection vers le changement de mot de passe...", juce::dontSendNotification);
}
