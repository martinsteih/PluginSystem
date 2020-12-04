#include "../../include/RtRuntime/RtThread.hpp"

#include <pthread.h>
#include <syscall.h>
#include <unistd.h>

struct sched_attr {
  sched_attr() = default;
  sched_attr(uint64_t runtime, uint64_t deadline, uint64_t period,
             uint32_t policy)
      : sched_policy{policy},
        sched_runtime{runtime},
        sched_deadline{deadline},
        sched_period{period} {}
  uint32_t size{sizeof(sched_attr)};
  uint32_t sched_policy;
  uint64_t sched_flags;
  uint32_t sched_nice;
  int32_t sched_priority;
  uint64_t sched_runtime;
  uint64_t sched_deadline;
  uint64_t sched_period;
};

RtThread::RtThread(SchedParams params, std::function<void()> function)
    : params{params}, callable{function}, thread{} {}
    
void RtThread::Start() {
  thread = std::thread{callable};
  set_attributes(params);

  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(1, &set);
  sched_setaffinity(thread.native_handle(), CPU_SETSIZE, &set);
}

long int RtThread::sched_setattr(SchedParams params, unsigned int flags) {
  sched_attr attr{static_cast<uint64_t>(params.runtime.count()), static_cast<uint64_t>(params.deadline.count()),
                  static_cast<uint64_t>(params.period.count()), static_cast<uint32_t>(params.policy)};
  return syscall(__NR_sched_setattr, thread.native_handle(), &attr, flags);
}

void RtThread::set_attributes(SchedParams params) { sched_setattr(params, 0); }
