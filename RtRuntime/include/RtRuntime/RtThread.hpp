#pragma once
#include <chrono>
#include <functional>
#include <thread>

class RtThread {
 public:
  struct SchedParams {
    enum class SchedPolicy {
      OTHER = 0,
      FIFO = 1,
      RR = 2,
      BATCH = 3,
      ISO = 4,
      IDLE = 5,
      DEADLINE = 6,
      RESET_ON_FORK = 0x40000000
    };

    std::chrono::microseconds period;
    std::chrono::microseconds deadline;
    std::chrono::microseconds runtime;
    SchedPolicy policy;
  };

  RtThread(SchedParams params, std::function<void(void)> function);

  ~RtThread() { thread.join(); }

  void Start();

 private:
  long int sched_setattr(SchedParams params, unsigned int flags);

  void set_attributes(SchedParams params);

  SchedParams params;
  std::function<void(void)> callable;
  std::thread thread;
};
