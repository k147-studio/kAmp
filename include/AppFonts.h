#pragma once

#include <JuceHeader.h>

class AppFonts
{
public:
    static void initialise();

    static juce::FontOptions regular(float height);
    static juce::FontOptions bold(float height);
    static juce::FontOptions italic(float height);
    static juce::FontOptions boldItalic(float height);

private:
    static juce::Typeface::Ptr regularTypeface;
    static juce::Typeface::Ptr boldTypeface;
    static juce::Typeface::Ptr italicTypeface;
    static juce::Typeface::Ptr boldItalicTypeface;
};
