#include <JuceHeader.h>
#include "EffectsFactory.h"
#include "MainComponent.h"

class GuiAppApplication final : public JUCEApplication {
public:
	GuiAppApplication() = default;

	const String getApplicationName() override {
		return JUCE_APPLICATION_NAME_STRING;
	}

	const String getApplicationVersion() override {
		return JUCE_APPLICATION_VERSION_STRING;
	}

	bool moreThanOneInstanceAllowed() override { return false; }

	void initialise(const String& commandLine) override {
		// This method is where you should put your application's initialisation code..
		ignoreUnused(commandLine);

		mainWindow = std::make_unique<MainWindow>(getApplicationName());
	}

	void shutdown() override {
		mainWindow = nullptr; // (deletes our window)
	}

	void systemRequestedQuit() override {
		// This is called when the app is being asked to quit: you can ignore this
		// request and let the app carry on running, or call quit() to allow the app to close.
		quit();
	}

	void anotherInstanceStarted(const String& commandLine) override {
		// When another instance of the app is launched while this one is running,
		// this method is invoked, and the commandLine parameter tells you what
		// the other instance's command-line arguments were.
		ignoreUnused(commandLine);
	}

	class MainWindow final : public DocumentWindow {
	public:
		explicit MainWindow(const String& name) :
			DocumentWindow(
				name, Desktop::getInstance().getDefaultLookAndFeel().findColour(
					backgroundColourId), allButtons) {
			setUsingNativeTitleBar(true);
			Pedalboard* pedalboard = new Pedalboard();
			pedalboard->appendAll(EffectsFactory::createAllEffects());
			Manager* manager = new Manager(pedalboard);
			setContentOwned(new MainComponent(*manager), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
#else
			setResizable(true, true);
			setSize(1280, 854);
			centreWithSize(1280, 854);
#endif
			Component::setVisible(true);
		}

		void closeButtonPressed() override {
			// This is called when the user tries to close this window. Here, we'll just
			// ask the app to quit when this happens, but you can change this to do
			// whatever you need.
			getInstance()->systemRequestedQuit();
		}

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
	};

private:
	std::unique_ptr<MainWindow> mainWindow;
};

// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(GuiAppApplication)
