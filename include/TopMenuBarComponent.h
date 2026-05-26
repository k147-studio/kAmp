#pragma once

#include "AccountComponent.h"
#include "ChromaticTunerComponent.h"
#include "LoginComponent.h"
#include "ModalOverlayComponent.h"
#include "SettingsComponent.h"
#include "TuningState.h"

#include <JuceHeader.h>
#include <atomic>
#include <memory>

class TopMenuBarComponent : public Component
{
public:
    explicit TopMenuBarComponent(AudioDeviceManager& deviceManager,
                                 std::atomic<bool>* isMuted = nullptr,
                                 TuningState* tuningState = nullptr);
    ~TopMenuBarComponent() override;

    void paint(Graphics& g) override;
    void resized() override;

    void closeAllModals();

private:
    static constexpr int buttonSize = 32;
    static constexpr float gap = 16.0f;

    FlexBox flexBox;

    DrawableButton accountButton { "account", DrawableButton::ImageFitted };
    DrawableButton muteButton { "mute", DrawableButton::ImageFitted };
    DrawableButton settingsButton { "settings", DrawableButton::ImageFitted };
    DrawableButton tunerButton { "tuner", DrawableButton::ImageFitted };

    std::unique_ptr<Drawable> muteIcon;
    std::unique_ptr<Drawable> unmuteIcon;

    AccountComponent* accountComponent = nullptr;
    LoginComponent* loginComponent = nullptr;
    ChromaticTunerComponent* tunerComponent = nullptr;
    std::unique_ptr<ModalOverlayComponent> modalOverlay;
    SettingsComponent* settingsComponent = nullptr;

    std::atomic<bool>* isSoundMuted = nullptr;
    TuningState* tuningState = nullptr;
    bool isLoggedIn = false;

    void updateMuteButtonImage();
    void dismissModal();

    void openSettingsPopup(AudioDeviceManager& deviceManager);
    void openAccountPopup();
    void openLoginPopup();
    void showAccountScreen();
    void openTunerPopup();
    void toggleMute();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopMenuBarComponent)
};
