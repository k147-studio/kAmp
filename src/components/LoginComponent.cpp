#include "LoginComponent.h"
#include "AppFonts.h"
#include "BinaryData.h"

namespace
{
const Colour brandColour (0xfff4efe8);
const Colour mutedTextColour (0xffc8bdb0);
const Colour fieldFillColour (0x33221818);
const Colour accentColour (0xffd4a017);
const Colour accentPressedColour (0xffb8860b);
const Colour overlayTopColour (0xcc1a1614);
const Colour overlayBottomColour (0xee0e0c0b);
}

LoginComponent::LoginComponent(LoginCallback loginSuccess, LoginCallback cancel)
    : onLoginSuccess(std::move(loginSuccess)),
      onCancel(std::move(cancel))
{
    logoImage = ImageFileFormat::loadFrom(BinaryData::kamp_logo_with_background_png,
                                          static_cast<size_t>(BinaryData::kamp_logo_with_background_pngSize));

    setOpaque(true);
    setInterceptsMouseClicks(true, true);

    brandLabel.setText("kAmp", dontSendNotification);
    brandLabel.setJustificationType(Justification::centred);
    brandLabel.setColour(Label::textColourId, brandColour);
    brandLabel.setFont(AppFonts::boldItalic(64.0f));
    addAndMakeVisible(brandLabel);

    taglineLabel.setText("Shape your tone. Own the chain.", dontSendNotification);
    taglineLabel.setJustificationType(Justification::centred);
    taglineLabel.setColour(Label::textColourId, mutedTextColour);
    taglineLabel.setFont(AppFonts::regular(18.0f));
    addAndMakeVisible(taglineLabel);

    statusLabel.setText({}, dontSendNotification);
    statusLabel.setJustificationType(Justification::centred);
    statusLabel.setColour(Label::textColourId, Colour(0xffffb4a2));
    statusLabel.setFont(AppFonts::regular(14.0f));
    addAndMakeVisible(statusLabel);

    setupFields();
    setupButtons();
    updateFocusOrder();

    animationStartMs = Time::getMillisecondCounter();
    startTimerHz(60);
}

LoginComponent::~LoginComponent()
{
    stopTimer();
}

void LoginComponent::setupFields()
{
    styleEditor(usernameField, "Email or username");
    styleEditor(passwordField, "Password");
    passwordField.setPasswordCharacter(juce::juce_wchar(0x2022)); // bullet

    usernameField.onReturnKey = [this] { passwordField.grabKeyboardFocus(); };
    passwordField.onReturnKey = [this] { attemptLogin(); };

    addAndMakeVisible(usernameField);
    addAndMakeVisible(passwordField);
}

void LoginComponent::styleEditor(TextEditor& editor, const String& placeholder)
{
    editor.setTextToShowWhenEmpty(placeholder, mutedTextColour.withAlpha(0.7f));
    editor.setFont(AppFonts::regular(16.0f));
    editor.setIndents(14, 8);
    editor.setColour(TextEditor::backgroundColourId, fieldFillColour);
    editor.setColour(TextEditor::outlineColourId, Colours::transparentBlack);
    editor.setColour(TextEditor::focusedOutlineColourId, accentColour.withAlpha(0.85f));
    editor.setColour(TextEditor::textColourId, brandColour);
    editor.setColour(TextEditor::highlightedTextColourId, Colours::black);
    editor.setColour(TextEditor::highlightColourId, accentColour.withAlpha(0.45f));
    editor.setColour(CaretComponent::caretColourId, accentColour);
}

void LoginComponent::setupButtons()
{
    loginButton.setColour(TextButton::buttonColourId, accentColour);
    loginButton.setColour(TextButton::buttonOnColourId, accentPressedColour);
    loginButton.setColour(TextButton::textColourOffId, Colour(0xff1a1408));
    loginButton.setColour(TextButton::textColourOnId, Colour(0xff1a1408));
    loginButton.onClick = [this] { attemptLogin(); };
    addAndMakeVisible(loginButton);

    cancelButton.setColour(TextButton::buttonColourId, Colours::transparentBlack);
    cancelButton.setColour(TextButton::buttonOnColourId, Colours::transparentBlack);
    cancelButton.setColour(TextButton::textColourOffId, mutedTextColour);
    cancelButton.setColour(TextButton::textColourOnId, brandColour);
    cancelButton.setMouseCursor(MouseCursor::PointingHandCursor);
    cancelButton.onClick = [this] { cancelLogin(); };
    addAndMakeVisible(cancelButton);
}

void LoginComponent::updateFocusOrder()
{
    usernameField.setExplicitFocusOrder(1);
    passwordField.setExplicitFocusOrder(2);
    loginButton.setExplicitFocusOrder(3);
    cancelButton.setExplicitFocusOrder(4);
}

void LoginComponent::visibilityChanged()
{
    if (isVisible())
    {
        contentAlpha = 0.0f;
        animationStartMs = Time::getMillisecondCounter();
        startTimerHz(60);
        toFront(true);
        usernameField.grabKeyboardFocus();
    }
    else
    {
        stopTimer();
    }
}

void LoginComponent::timerCallback()
{
    const auto elapsed = static_cast<int>(Time::getMillisecondCounter() - animationStartMs);
    contentAlpha = jlimit(0.0f, 1.0f, static_cast<float>(elapsed) / static_cast<float>(animationDurationMs));

    // Ease-out cubic.
    const float t = contentAlpha;
    contentAlpha = 1.0f - std::pow(1.0f - t, 3.0f);

    brandLabel.setAlpha(contentAlpha);
    taglineLabel.setAlpha(contentAlpha);
    usernameField.setAlpha(contentAlpha);
    passwordField.setAlpha(contentAlpha);
    loginButton.setAlpha(contentAlpha);
    cancelButton.setAlpha(contentAlpha);
    statusLabel.setAlpha(contentAlpha);
    repaint();

    if (elapsed >= animationDurationMs)
    {
        contentAlpha = 1.0f;
        stopTimer();
    }
}

void LoginComponent::paint(Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    ColourGradient wash(overlayTopColour, 0.0f, 0.0f,
                        overlayBottomColour, 0.0f, bounds.getHeight(), false);
    g.setGradientFill(wash);
    g.fillAll();

    if (!formBounds.isEmpty())
    {
        g.setOpacity(0.55f * contentAlpha);
        g.setColour(Colour(0xff161210));
        g.fillRoundedRectangle(formBounds, 18.0f);

        g.setOpacity(contentAlpha);
        g.setColour(Colour(0x33e8dcc8));
        g.drawRoundedRectangle(formBounds.reduced(0.5f), 18.0f, 1.0f);
    }

    if (logoImage.isValid())
    {
        constexpr float logoSize = 72.0f;
        const float logoY = formBounds.getY() - logoSize - 28.0f;
        const float logoX = formBounds.getCentreX() - logoSize * 0.5f;
        g.setOpacity(contentAlpha);
        g.drawImage(logoImage, Rectangle<float>(logoX, logoY, logoSize, logoSize));
    }
}

void LoginComponent::resized()
{
    const auto bounds = getLocalBounds();
    const int formWidth = jmin(380, bounds.getWidth() - 48);
    const int fieldHeight = 46;
    const int buttonHeight = 48;
    const int gap = 12;
    const int formPadding = 28;
    const int formInnerHeight = fieldHeight * 2 + buttonHeight * 2 + gap * 4 + 8;
    const int formHeight = formInnerHeight + formPadding * 2;

    formBounds = Rectangle<float>(static_cast<float>((bounds.getWidth() - formWidth) / 2),
                                  static_cast<float>(bounds.getCentreY() - formHeight / 2 + 36),
                                  static_cast<float>(formWidth),
                                  static_cast<float>(formHeight));

    auto form = formBounds.toNearestIntEdges().reduced(formPadding);

    usernameField.setBounds(form.removeFromTop(fieldHeight));
    form.removeFromTop(gap);
    passwordField.setBounds(form.removeFromTop(fieldHeight));
    form.removeFromTop(gap + 4);
    loginButton.setBounds(form.removeFromTop(buttonHeight));
    form.removeFromTop(gap);
    cancelButton.setBounds(form.removeFromTop(buttonHeight));

    const int brandWidth = formWidth + 40;
    const int brandX = (bounds.getWidth() - brandWidth) / 2;
    const int brandY = static_cast<int>(formBounds.getY()) - 72 - 28 - 70;
    brandLabel.setBounds(brandX, jmax(24, brandY), brandWidth, 70);
    taglineLabel.setBounds(brandX, brandLabel.getBottom() - 4, brandWidth, 28);

    statusLabel.setBounds(static_cast<int>(formBounds.getX()),
                          static_cast<int>(formBounds.getBottom()) + 14,
                          formWidth,
                          22);
}

void LoginComponent::attemptLogin()
{
    const auto user = usernameField.getText().trim();
    const auto pass = passwordField.getText();

    if (user.isEmpty() || pass.isEmpty())
    {
        statusLabel.setText("Enter your email and password to continue.", dontSendNotification);
        if (user.isEmpty())
            usernameField.grabKeyboardFocus();
        else
            passwordField.grabKeyboardFocus();
        return;
    }

    // Auth backend is not wired yet — accept any non-empty credentials for now.
    statusLabel.setText({}, dontSendNotification);
    if (onLoginSuccess != nullptr)
        onLoginSuccess();
}

void LoginComponent::cancelLogin()
{
    if (onCancel != nullptr)
        onCancel();
}
