#include "../../include/RtRuntime/NamedEvent.hpp"

#include <boost/interprocess/sync/scoped_lock.hpp>

const char* prepare_mutex(std::string name, bool server) {
  if (server) named_mutex::remove(name.c_str());
  return name.c_str();
}

const char* prepare_condition(std::string name, bool server) {
  if (server) named_condition::remove(name.c_str());
  return name.c_str();
}

NamedEvent::NamedEvent(std::string name, bool server)
    : mutex_name{name + "_mtx"},
      cond_name{name + "_cnd"},
      mutex{open_or_create, prepare_mutex(mutex_name, server)},
      cond{open_or_create, prepare_condition(cond_name, server)} {}

void NamedEvent::Signal() { cond.notify_all(); }

void NamedEvent::Wait() {
  scoped_lock<named_mutex> lock{mutex};
  cond.wait(lock);
}
