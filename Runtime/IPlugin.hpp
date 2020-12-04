#pragma once
#include <functional>

struct IPlugin{
    virtual ~IPlugin() = default;
    virtual void Run() = 0;
    std::function<void()> InputCycle{nullptr};
    std::function<void()> OutputCycle{nullptr};
};
