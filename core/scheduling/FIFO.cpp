#include "FIFO.h"

FIFO::FIFO()
: IScheduler(3)
{}

FIFO::FIFO(size_t size)
: IScheduler(size)
{}

void FIFO::run(void)
{
    size_t index = 0;
    size_t time = 0;
    Process* p = &(this->processList->at(index));

    std::cout << "FIFO running with " << this->processList->size() << " jobs.\n";
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