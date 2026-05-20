#pragma once

#include <atomic>

/**
 * @brief Lock-free tuning snapshot published by the audio thread and read by the UI.
 */
struct TuningState
{
    std::atomic<bool> enabled { false };
    std::atomic<bool> hasSignal { false };
    std::atomic<bool> isInTune { false };
    std::atomic<float> frequency { 0.0f };
    std::atomic<float> cents { 0.0f };
    std::atomic<int> midiNote { -1 };
};
