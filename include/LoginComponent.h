#pragma once

#include <JuceHeader.h>

#include <functional>

/**
 * @brief Branded sign-in form shown when the user opens Account while logged out.
 */
class LoginComponent final : public Component,
                             private Timer
{
public:
    using LoginCallback = std::function<void()>;

    explicit LoginComponent(LoginCallback onLoginSuccess, LoginCallback onCancel = {});
    ~LoginComponent() override;

    void paint(Graphics&) override;
    void resized() override;
    void visibilityChanged() override;

private:
    void timerCallback() override;
    void setupFields();
    void setupButtons();
    void styleEditor(TextEditor& editor, const String& placeholder);
    void attemptLogin();
    void cancelLogin();
    void updateFocusOrder();

    LoginCallback onLoginSuccess;
    LoginCallback onCancel;

    Image logoImage;

    Label brandLabel;
    Label taglineLabel;
    Label statusLabel;

    TextEditor usernameField;
    TextEditor passwordField;

    TextButton loginButton { "Sign in" };
    TextButton cancelButton { "Cancel" };

    Rectangle<float> formBounds;
    float contentAlpha = 0.0f;
    uint32 animationStartMs = 0;
    static constexpr int animationDurationMs = 520;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};
