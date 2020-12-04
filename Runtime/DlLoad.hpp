#pragma once

#include <memory>
#include <string>
#include "IPlugin.hpp"


class DlLoad{
    public:
        explicit DlLoad(std::string path);
        ~DlLoad();
        std::unique_ptr<IPlugin> GetPlugin(std::string name);

    private:
        using getter = std::unique_ptr<IPlugin> (*)();
        void *dl_handle{nullptr};
        getter symbol{nullptr};
};