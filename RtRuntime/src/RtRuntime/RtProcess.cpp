#include "../../include/RtRuntime/RtProcess.hpp"

#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>

#include <chrono>
#include <fstream>
#include <sstream>

void prefault_stack() {
  rlimit limit;
  int size{ getrlimit(RLIMIT_STACK, &limit) };
  unsigned char dummy[limit.rlim_cur];
  int i;
  for (i = 0; i < size; i += sysconf(_SC_PAGESIZE)) dummy[i] = 1;
}

void prefault_heap(size_t size) {
  char* dummy;
  int i;
  dummy = static_cast<char*>(malloc(size));
  if (!dummy) return;
  for (i = 0; i < size; i += sysconf(_SC_PAGESIZE)) dummy[i] = 1;
  free(dummy);
}

void set_cpuset(size_t cpu) {
  std::stringstream tmp_stream;
  tmp_stream << "/sys/fs/cgroup/cpuset/cpu" << cpu << "/tasks";
  std::ofstream of{tmp_stream.str()};
  of << getpid();
}

void RtProcess::prepare(RtProcess::Params params) {
  mlockall(MCL_CURRENT | MCL_FUTURE);
  prefault_stack();
  //prefault_heap(params.heap_size);
  // set_cpuset(params.cgroup_cpu);
}
