#pragma once

#include "Pedalboard.h"

#include <memory>

/**
 * @brief Session API for mutating the pedalboard and notifying the UI.
 * Audio processing lives in AudioEngine; this class is the sole graph editor surface.
 */
class Manager : public juce::ChangeBroadcaster
{
public:
    explicit Manager(Pedalboard& pedalboard);

    Pedalboard& getPedalboard() noexcept;
    [[nodiscard]] const Pedalboard& getPedalboard() const noexcept;

    void append(std::unique_ptr<AbstractEffect> effect);
    void remove(const AbstractEffect* effect);
    void move(const AbstractEffect* dragged, const AbstractEffect* target);

    bool importFromFile(const File& file);
    bool exportToFile(const File& file) const;

private:
    Pedalboard& pedalboard;
};
