#ifndef RoundRobin_EXISTS 
#define RoundRobin_EXISTS
#include "../process/Process.h"
#include "IScheduler.h"
#include <unordered_set>
#include <cstddef>

class RoundRobin: public IScheduler
{
    protected:
        size_t quantum;
        std::unordered_set<Process*> lookUp;
    public:
        RoundRobin();
        RoundRobin(size_t processCount);
        RoundRobin(size_t processCount, size_t quantum);
        void setQuantum(size_t quantum);
        size_t getQuantum(void);
        void run(void);
};

#endif