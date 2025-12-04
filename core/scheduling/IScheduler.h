#ifndef IScheduler_EXISTS
#define IScheduler_EXISTS
#include "../process/Process.h"
#include "../metrics/scheduling/ExecutionMetric.h"
#include <vector>
#include <cstddef>
#include <algorithm>

class IScheduler 
{
    protected:
        std::vector<Process>* processList;
        size_t size;
    public:
        IScheduler();
        IScheduler(size_t size);
        void displayMetrics(void);
        virtual void run(void) = 0;
        void sortProcessesDecending(void);
        void sortProcessExecutionTimeDecending(void);
        void randomizeProcessArrivalTime(void);
        ~IScheduler();        
};

#endif