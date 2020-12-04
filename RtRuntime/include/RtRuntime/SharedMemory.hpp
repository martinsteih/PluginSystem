#pragma once
#include <string>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

class SharedMemory {
public:
    SharedMemory(std::string name, size_t size);

    uint8_t* get_memory();

    template<typename T>
    auto get_type_at(size_t offset) {
        if (auto size(sizeof(T)); size + offset <= region.get_size()) {
            return *reinterpret_cast<T*>(region.get_address());
        }
        else {
            throw std::exception{  }; //"Access beyond shared memory area!"
        }
    }

    template<typename T>
    void set_type_at(T value, size_t offset) {
        if (auto size(sizeof(T)); size + offset <= region.get_size()) {
            *reinterpret_cast<T*>(region.get_address()) = value;
        }
        else {
            throw std::exception{  }; //"Access beyond shared memory area!"
        }
    }

private:
    shared_memory_object shm;
    mapped_region region;
};