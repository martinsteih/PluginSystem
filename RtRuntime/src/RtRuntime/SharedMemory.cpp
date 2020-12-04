#include "../../include/RtRuntime/SharedMemory.hpp"

SharedMemory::SharedMemory(std::string name, size_t size)
    : shm{open_or_create, name.c_str(), read_write} {
  shm.truncate(size);
  region = mapped_region{shm, read_write};
}

uint8_t* SharedMemory::get_memory() {
  return static_cast<uint8_t*>(region.get_address());
}
