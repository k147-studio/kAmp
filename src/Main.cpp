#include <JuceHeader.h>

#include "AppFonts.h"
#include "EffectRegistry.h"
#include "MainComponent.h"
#include "Pedalboard.h"

class GuiAppApplication final : public JUCEApplication
{
public:
    GuiAppApplication() = default;

    const String getApplicationName() override
    {
        return JUCE_APPLICATION_NAME_STRING;
    }

    const String getApplicationVersion() override
    {
        return JUCE_APPLICATION_VERSION_STRING;
    }

    bool moreThanOneInstanceAllowed() override { return false; }

    void initialise(const String& commandLine) override
    {
        ignoreUnused(commandLine);
        AppFonts::initialise();
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted(const String& commandLine) override
    {
        ignoreUnused(commandLine);
    }

    class MainWindow final : public DocumentWindow
    {
    public:
        explicit MainWindow(const String& name)
            : DocumentWindow(name,
                             Desktop::getInstance().getDefaultLookAndFeel().findColour(backgroundColourId),
                             allButtons)
        {
            setUsingNativeTitleBar(true);

            auto pedalboard = std::make_unique<Pedalboard>();
            pedalboard->appendAll(EffectRegistry::createDefaultEffects());
            setContentOwned(new MainComponent(std::move(pedalboard)), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(true, true);
            setSize(1280, 854);
            centreWithSize(1280, 854);
#endif
            Component::setVisible(true);
        }

        void closeButtonPressed() override
        {
            getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(GuiAppApplication)
