#include "../../include/RtRuntime/RuntimeBase.hpp"

RuntimeBase::RuntimeBase(RtThread::SchedParams params, std::function<void()> callable)
    : cycle{ params, callable} {}

void RuntimeBase::Start() {
    cycle.Start();
}