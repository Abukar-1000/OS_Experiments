#include "RoundRobin.h"

RoundRobin::RoundRobin()
:   IScheduler(3),
    quantum(10),
    lookUp(std::unordered_set<Process*>())
{
    this->lookUp.reserve(this->processList->size());
}

RoundRobin::RoundRobin(size_t processCount)
:   IScheduler(processCount),
    quantum(10),
    lookUp(std::unordered_set<Process*>())
{
    this->lookUp.reserve(this->processList->size());
}

RoundRobin::RoundRobin(size_t processCount, size_t quantum)
:   IScheduler(processCount),
    quantum(quantum)
{
    this->lookUp.reserve(this->processList->size());
}

void RoundRobin::setQuantum(size_t quantum)
{
    this->quantum = quantum;
}

size_t RoundRobin::getQuantum(void)
{
    return this->quantum;
}

void RoundRobin::run(void)
{
    size_t index = 0;
    size_t time = 0;
    Process* p = &(this->processList->at(index));

    std::cout << "Round Robin running with " << this->processList->size() << " jobs.\n";
    while (this->lookUp.size() < this->processList->size())
    {
        if (!p->hasRun())
        {
            p->setFirstRunTime(time);
        }
        
        p->run(this->quantum);
        if (p->isComplete())
        {
            auto search = this->lookUp.find(p);
            bool isPreviouslyCompletedProcess = search != this->lookUp.end();
            if (isPreviouslyCompletedProcess)
            {
                index++;
                if (index == this->processList->size())
                {
                    index = 0;
                }

                p = &(this->processList->at(index));
                continue;
            }

            p->setCompletionTime(time);
            this->lookUp.insert(p);
        }
        
        index++;
        if (index == this->processList->size())
        {
            index = 0;
        }
        p = &(this->processList->at(index));
    }
}