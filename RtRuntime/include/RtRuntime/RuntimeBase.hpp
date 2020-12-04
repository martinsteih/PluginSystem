#pragma once
#include "RtThread.hpp"
#include <iostream>

class RuntimeBase {
public:
    explicit RuntimeBase(RtThread::SchedParams params, std::function<void()> callable);

    virtual ~RuntimeBase() = default;

protected:
    void Start();
private:
    RtThread cycle;
};