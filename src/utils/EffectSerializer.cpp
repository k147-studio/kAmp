#pragma once

#include <JuceHeader.h>
#include <memory>
#include <vector>
#include "AbstractEffect.h"
#include "DelayEffect.h"

class EffectSerializer {
public:
    /**
     * @brief Saves a list of effects to a JSON file.
     * @param effects Vector of effect pointers to serialize
     * @param filePath Path to save the JSON file
     * @return True if saving succeeded, false otherwise
     */
    static bool saveEffectsToFile(const std::vector<std::shared_ptr<AbstractEffect> > &effects, const File &filePath) {
        const auto effectsArray = var(Array<var>());
        Array<var> *array = effectsArray.getArray();

        for (const auto &effect: effects) {
            array->add(effect->toJSON());
        }

        DynamicObject *root = new DynamicObject();
        root->setProperty("effects", effectsArray);

        String jsonString = JSON::toString(root);
        return filePath.replaceWithText(jsonString);
    }

    /**
     * @brief Loads effects from a JSON file.
     * @param filePath Path to the JSON file
     * @return Vector of loaded effect pointers
     */
    static std::vector<std::shared_ptr<AbstractEffect> > loadEffectsFromFile(const File &filePath) {
        std::vector<std::shared_ptr<AbstractEffect> > loadedEffects;

        if (!filePath.existsAsFile()) {
            return loadedEffects;
        }

        const String jsonContent = filePath.loadFileAsString();
        const auto rootVar = JSON::parse(jsonContent);

        if (const auto *root = rootVar.getDynamicObject()) {
            const auto effectsVar = root->getProperty("effects");

            if (auto *effectsArray = effectsVar.getArray()) {
                for (const auto &effectVar: *effectsArray) {
                    if (const auto *effectObj = effectVar.getDynamicObject()) {
                        String type = effectObj->getProperty("type").toString();

                        if (std::shared_ptr<AbstractEffect> effect = createEffectFromType(type)) {
                            effect->fromJSON(effectVar);
                            loadedEffects.push_back(effect);
                        }
                    }
                }
            }
        }

        return loadedEffects;
    }

private:
    /**
     * @brief Creates an effect instance based on its type string.
     * @param type The type name of the effect
     * @return Shared pointer to the created effect, or nullptr if type is unknown
     */
    static std::shared_ptr<AbstractEffect> createEffectFromType(const String &type) {
        if (type == "DelayEffect")
            return std::make_shared<DelayEffect>();
        // Add more effect types here as needed

        return nullptr;
    }
};
