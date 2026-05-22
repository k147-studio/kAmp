#include "ResourceManager.h"

#include "BinaryData.h"

std::unique_ptr<Drawable> ResourceManager::powerIcon;
std::unique_ptr<Drawable> ResourceManager::closeIcon;

std::unique_ptr<Drawable> ResourceManager::loadSvg(const char* data, int dataSize)
{
    return Drawable::createFromImageData(data, static_cast<size_t>(dataSize));
}

void ResourceManager::configureIconButton(DrawableButton& button, const Drawable& icon)
{
    button.setImages(&icon);
    button.setColour(DrawableButton::backgroundColourId, Colours::transparentBlack);
    button.setColour(DrawableButton::backgroundOnColourId, Colours::transparentBlack);
    button.setEdgeIndent(2);
}

const Drawable& ResourceManager::getPowerIcon()
{
    if (powerIcon == nullptr)
        powerIcon = loadSvg(BinaryData::power_svg, BinaryData::power_svgSize);

    jassert(powerIcon != nullptr);
    return *powerIcon;
}

const Drawable& ResourceManager::getCloseIcon()
{
    if (closeIcon == nullptr)
        closeIcon = loadSvg(BinaryData::xmark_svg, BinaryData::xmark_svgSize);

    jassert(closeIcon != nullptr);
    return *closeIcon;
}
