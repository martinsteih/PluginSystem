#pragma once
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <string>

using namespace boost::interprocess;

class NamedEvent {
public:
    NamedEvent(std::string name, bool server);

    void Signal();

    void Wait();

private:
    std::string mutex_name;
    std::string cond_name;
    named_mutex mutex;
    named_condition cond;
};