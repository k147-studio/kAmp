#include "AppFonts.h"

#include "BinaryData.h"

juce::Typeface::Ptr AppFonts::regularTypeface;
juce::Typeface::Ptr AppFonts::boldTypeface;
juce::Typeface::Ptr AppFonts::italicTypeface;
juce::Typeface::Ptr AppFonts::boldItalicTypeface;

void AppFonts::initialise()
{
    regularTypeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::InterRegular_ttf, static_cast<size_t>(BinaryData::InterRegular_ttfSize));
    boldTypeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::InterBold_ttf, static_cast<size_t>(BinaryData::InterBold_ttfSize));
    italicTypeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::InterItalic_ttf, static_cast<size_t>(BinaryData::InterItalic_ttfSize));
    boldItalicTypeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::InterBoldItalic_ttf, static_cast<size_t>(BinaryData::InterBoldItalic_ttfSize));

    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(regularTypeface);
}

juce::FontOptions AppFonts::regular(float height)
{
    return juce::FontOptions().withHeight(height).withTypeface(regularTypeface);
}

juce::FontOptions AppFonts::bold(float height)
{
    return juce::FontOptions().withHeight(height).withTypeface(boldTypeface);
}

juce::FontOptions AppFonts::italic(float height)
{
    return juce::FontOptions().withHeight(height).withTypeface(italicTypeface);
}

juce::FontOptions AppFonts::boldItalic(float height)
{
    return juce::FontOptions().withHeight(height).withTypeface(boldItalicTypeface);
}
