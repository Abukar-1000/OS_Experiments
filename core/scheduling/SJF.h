#ifndef SJF_EXISTS
#define SJF_EXISTS
#include "IScheduler.h"
#include "../process/Process.h"
#include <cstddef>

// Shortest Job First (SJF)
class SJF: public IScheduler
{
    public:
        SJF();
        SJF(size_t processCount);
        void run(void);
};

#endif