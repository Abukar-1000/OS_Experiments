#ifndef FIFO_EXISTS
#define FIFO_EXISTS
#include "IScheduler.h"
#include "../process/Process.h"
#include <cstddef>

class FIFO: public IScheduler
{
    public:
        FIFO();
        FIFO(size_t processCount);
        void run(void);
};
#endif