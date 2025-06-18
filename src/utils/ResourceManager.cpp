#include "ResourceManager.h"

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

Image ResourceManager::loadImage(const String &relativePath) {
    File imageFile;

#if JUCE_MAC || JUCE_IOS
    imageFile = File::getSpecialLocation(File::currentApplicationFile)
            .getParentDirectory()
            .getParentDirectory()
            .getParentDirectory()
            .getChildFile(relativePath);
#else
    imageFile = juce::File::getCurrentWorkingDirectory().getChildFile(relativePath);
#endif
    Image image = ImageFileFormat::loadFrom(imageFile);

    if (image.isNull()) {
        // DBG("Erreur : impossible de charger l'image à partir de " + imageFile.getFullPathName());
    }

    return image;
}
