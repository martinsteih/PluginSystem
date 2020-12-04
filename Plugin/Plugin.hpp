#pragma once
#include <iostream>
#include <memory>
#include <functional>

struct IPlugin{
    virtual ~IPlugin() = default;
    virtual void Run() = 0;
    std::function<void()> InputCycle{nullptr};
    std::function<void()> OutputCycle{nullptr};
};

class MyPlugin : public IPlugin{
public:
    MyPlugin();
    void Run() override;
    void Input();
    void Output();
};

extern "C"{
    std::unique_ptr<IPlugin> GetPlugin(){
        return std::make_unique<MyPlugin>();
    }
}