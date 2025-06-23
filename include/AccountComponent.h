#pragma once

#include <JuceHeader.h>

class AccountComponent : public Component {
public:
	AccountComponent();
	void paint(Graphics&) override;
	void resized() override;

private:
	void apiResponseReceived(const String& content);
	void saveSettings();
	void importSettings();

	void setupLabels();
	void setupButtons();
	void setupGrid();

	Label titleLabel{"titleLabel", "Mon compte"};
	Label responseLabel{"responseLabel", "En attente de réponse..."};

	Label emailLabel{"emailLabel", "Adresse mail :"};
	Label usernameLabel{"usernameLabel", "Nom d'utilisateur :"};
	Label emailValueLabel{"emailValueLabel", "utilisateur@example.com"};
	Label usernameValueLabel{"usernameValueLabel", "NomUtilisateur"};

	TextButton saveButton{"Sauvegarder les réglages"};
	TextButton importButton{"Importer les réglages"};

	Grid grid;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AccountComponent)
};