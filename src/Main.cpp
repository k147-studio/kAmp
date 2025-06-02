#include <JuceHeader.h>

#include "EffectsFactory.h"
#include "MainComponent.h"

class GuiAppApplication final : public JUCEApplication {
public:
    GuiAppApplication() = default;

    // We inject these as compile definitions from the CMakeLists.txt
    // If you've enabled the juce header with `juce_generate_juce_header(<thisTarget>)`
    // you could `#include <JuceHeader.h>` and use `ProjectInfo::projectName` etc. instead.
    const String getApplicationName() override { return JUCE_APPLICATION_NAME_STRING; }
    const String getApplicationVersion() override { return JUCE_APPLICATION_VERSION_STRING; }
    bool moreThanOneInstanceAllowed() override { return false; }

    void initialise(const String &commandLine) override {
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

    void anotherInstanceStarted(const String &commandLine) override {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
        ignoreUnused(commandLine);
    }

    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow final : public DocumentWindow {
    public:
        explicit MainWindow (String name)
            : DocumentWindow (name,
                              Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (backgroundColourId),
                              allButtons)
        {
            setUsingNativeTitleBar (true);
            Pedalboard* pedalboard = new Pedalboard();
            pedalboard->appendAll(EffectsFactory::createAllEffects());
            Manager* manager = new Manager(pedalboard);
            setContentOwned (new MainComponent(*manager), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
#else
            setResizable(false, false);
            centreWithSize(1280, 720);
#endif

            Component::setVisible(true);
        }

        void closeButtonPressed() override {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    // private:
    //     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(GuiAppApplication)
