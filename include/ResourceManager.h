#pragma once
#include <JuceHeader.h>

class ResourceManager {
public:
    ResourceManager();

    ~ResourceManager();

    static Image loadImage(const String &relativePath);
};
