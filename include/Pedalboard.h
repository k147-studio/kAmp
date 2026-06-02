#pragma once

#include "AbstractEffect.h"

#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>

#include <memory>
#include <vector>

/**
 * @brief Ordered effect chain that also behaves as a composite AbstractEffect.
 */
class Pedalboard : public AbstractEffect
{
public:
    Pedalboard();
    ~Pedalboard() override;

    Pedalboard(const Pedalboard&) = delete;
    Pedalboard& operator=(const Pedalboard&) = delete;

    void apply(const AudioSourceChannelInfo& bufferToFill) override;
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;

    bool operator==(const AbstractEffect* effect) override;

    void append(std::unique_ptr<AbstractEffect> effect);
    void appendAll(std::vector<std::unique_ptr<AbstractEffect>> newEffects);
    void insert(std::unique_ptr<AbstractEffect> effect, int index);
    void remove(const AbstractEffect* effect);

    /** Moves @p dragged so it sits where @p target currently is. */
    void move(const AbstractEffect* dragged, const AbstractEffect* target);

    void clear();

    [[nodiscard]] const std::vector<std::unique_ptr<AbstractEffect>>& getEffects() const noexcept;
    [[nodiscard]] std::vector<AbstractEffect*> getEffectPointers() const;

    [[nodiscard]] String getEffectType() const override { return "Pedalboard"; }

    [[nodiscard]] var toJSON() const override;
    void fromJSON(const var& json) override;

private:
    std::vector<std::unique_ptr<AbstractEffect>> effects;
    juce::dsp::ProcessSpec currentSpec { 44100.0, 512, 2 };
    bool isPrepared = false;
    juce::SpinLock processLock;
};
