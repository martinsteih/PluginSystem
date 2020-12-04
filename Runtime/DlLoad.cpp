#include <exception>
#include <dlfcn.h>
#include "DlLoad.hpp"

class SoException : public std::exception{
    public:
    explicit SoException(const char* message): message{message}{}
    const char* what() const noexcept override{
        return message;
    }
    private:
        const char *const message;
};

    DlLoad::DlLoad(std::string path){
        dl_handle = dlopen(path.c_str(), RTLD_LAZY);
        if(!dl_handle)
            throw SoException{"could not load shared library"};
    }

    DlLoad::~DlLoad(){
        if(dl_handle){
            dlclose(dl_handle);
            dl_handle = nullptr;
        }
    }

    std::unique_ptr<IPlugin> DlLoad::GetPlugin(std::string name){
        if(!dl_handle)
            throw SoException{"no shared library loaded"};
        if(!symbol){
            symbol = (getter)dlsym(dl_handle, name.c_str());
            if(!symbol){
                throw SoException{"could not load symbol"};
            }
                
        }
        return symbol();
    }