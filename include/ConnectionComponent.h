#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

/**
 * @brief Represents a graphical component that contains and displays the login form.
 */
class LoginComponent final : public juce::Component {
  public:
    /**
     * @brief Initializes a new instance of the LoginComponent class.
     */
    LoginComponent();

    /**
     * @brief Destroys the instance of the LoginComponent class.
     */
    ~LoginComponent() override;

    /**
     * @brief Determines how to display the component.
     * @param g The JUCE graphics context that paints the component.
     */
    void paint(juce::Graphics &g) override;

    /**
     * @brief Determines what to do when the component is resized.
     */
    void resized() override;
  private:
    /**
     * @brief The username field.
     */
    juce::TextEditor usernameField;

    /**
     * @brief The password field.
     */
    juce::TextEditor passwordField;

    /**
     * @brief The login button.
     */
    juce::TextButton loginButton;

    /**
     * @brief The skip button.
     */
    juce::TextButton skipButton;

    /**
     * @brief Determines what to do when the skip button is clicked.
     */
    void skipButtonClicked();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};