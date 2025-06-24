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

	Label responseLabel{"responseLabel", "Waiting for response..."};

	Label emailLabel{"emailLabel", "Email :"};
	Label usernameLabel{"usernameLabel", "Username :"};
	Label emailValueLabel{"emailValueLabel", "user@example.com"};
	Label usernameValueLabel{"usernameValueLabel", "Username"};

	TextButton saveButton{"Save presets" };
	TextButton importButton{"Sync presets" };

	Grid grid;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AccountComponent)
};