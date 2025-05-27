#include "ResourceManager.h"

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

juce::Image ResourceManager::loadImage(const juce::String& relativePath)
{
    juce::File imageFile;

#if JUCE_MAC
    imageFile = juce::File::getSpecialLocation(juce::File::currentApplicationFile)
                    .getParentDirectory()
                    .getParentDirectory()
                    .getParentDirectory()
                    .getChildFile(relativePath);
#else
    imageFile = juce::File::getCurrentWorkingDirectory().getChildFile(relativePath);
#endif

    juce::Image image = juce::ImageFileFormat::loadFrom(imageFile);

    if (image.isNull())
    {
        DBG("Erreur : impossible de charger l'image à partir de " + imageFile.getFullPathName());
    }

    return image; // retourne un objet juce::Image valide ou invalide (mais jamais nullptr)
}
