#pragma once
#include <JuceHeader.h>
#include <memory>

class ResourceManager
{
public:
    static std::unique_ptr<Drawable> loadSvg(const char* data, int dataSize);
    static void configureIconButton(DrawableButton& button, const Drawable& icon);
    static const Drawable& getPowerIcon();
    static const Drawable& getCloseIcon();

private:
    static std::unique_ptr<Drawable> powerIcon;
    static std::unique_ptr<Drawable> closeIcon;
};
