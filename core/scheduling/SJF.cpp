#include "SJF.h"
#include <algorithm>

SJF::SJF()
:   IScheduler(3)
{}

SJF::SJF(size_t size)
:   IScheduler(size)
{}

void SJF::run(void)
{
    size_t index = 0;
    size_t time = 0;
    this->randomizeProcessArrivalTime();
    this->sortProcessExecutionTimeDecending();

    Process* p = &(this->processList->at(index));

    std::cout << "SJF running with " << this->processList->size() << " jobs.\n";
    while (index < this->processList->size())
    {
        if (!p->hasRun())
        {
            p->setFirstRunTime(time);
        }

        if (p->isComplete())
        {
            p->setCompletionTime(time);
            index++;

            if (index < this->processList->size())
            {
                p = &(this->processList->at(index));
            }
            continue;
        }

        p->run(1);
        time++;
    }
}