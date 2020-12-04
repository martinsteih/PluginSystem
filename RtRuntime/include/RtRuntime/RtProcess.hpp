#pragma once
#include <cinttypes>

struct RtProcess {
  struct Params {
    Params(uint64_t stack_size, uint64_t heap_size, uint64_t cgroup_cpu)
        : stack_size{stack_size},
          heap_size{heap_size},
          cgroup_cpu{cgroup_cpu} {}
    Params()
        : Params(512 * 1024, 10 * 512 * 1024, 1) {}

    uint64_t stack_size;
    uint64_t heap_size;
    uint64_t cgroup_cpu;
  };
  static void prepare(Params params);
};
