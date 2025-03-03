#pragma once
#include "IEffect.h"
#include <string>

class AbstractEffect : public IEffect {
  public:
    AbstractEffect() = default;
    ~AbstractEffect() override = default;
    std::string getAuthor();
    std::string getDescription();
    std::string getVersion();
    virtual bool operator==(const AbstractEffect* effect) = 0;
    void apply(const juce::AudioSourceChannelInfo &bufferToFill) override = 0;

  private:
    std::string author;
    std::string description;
    std::string version;
};