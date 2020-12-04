#include <iostream>
#include <exception>
#include <memory>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

#include "DlLoad.hpp"

class Runtime{
    public:
        explicit Runtime(std::string libname, std::string plugin_name) : lib{libname}, plugin_name{plugin_name}{

        }
    void run() {
        while(true){
            plugin = lib.GetPlugin(plugin_name);
            if(!plugin)
                throw std::exception{};
            if(plugin->InputCycle)
                plugin->InputCycle();
            plugin->Run();
            if(plugin->OutputCycle)
                plugin->OutputCycle();
            std::cout << std::endl;
            std::this_thread::sleep_for(1s);
        }
    }

    private:
        DlLoad lib;
        std::string plugin_name;
        std::unique_ptr<IPlugin> plugin{nullptr};
};


auto main(int argc, char** argv)->int{
    if(argc < 2){
        exit(-1);
    }
    try{
        Runtime rt{argv[1], argv[2]};
        rt.run();
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}