#include "Plugin.hpp"

MyPlugin::MyPlugin()
{
    InputCycle = [&]() { Input(); };
    OutputCycle = [&]() { Output(); };
}

void MyPlugin::Input(){
    std::cout << "MyPlugin::Input()\n";
}

void MyPlugin::Output(){
    std::cout << "MyPlugin::Output()\n";
}

void MyPlugin::Run(){
        std::cout << "MyPlugin::Run()\n";
}

