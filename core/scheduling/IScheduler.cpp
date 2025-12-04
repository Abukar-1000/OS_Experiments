#include "IScheduler.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


IScheduler::IScheduler()
:   size(0),
    processList(nullptr)
{}

IScheduler::IScheduler(size_t _size)
:   size(_size)
{
    this->processList = new std::vector<Process>();
    this->processList->reserve(this->size);

    for (size_t i = 0; i < this->size; ++i)
    {
        Process p = Process();
        this->processList->push_back(p);
    }
}

void IScheduler::displayMetrics(void)
{
    metrics::scheduling::ExecutionMetric _metrics = metrics::scheduling::ExecutionMetric();
    _metrics.calculate(this->processList);
    std::cout <<  _metrics.display() << "\n";
}

void IScheduler::sortProcessesDecending(void)
{
    std::sort(
        this->processList->begin(), 
        this->processList->end(),
        [](Process& first, Process& second)
        {
            return first.getArrivalTime() < second.getArrivalTime();
        }
    );
}

void IScheduler::sortProcessExecutionTimeDecending(void)
{
    std::sort(
        this->processList->begin(), 
        this->processList->end(),
        [](Process& first, Process& second)
        {
            /**
             * @brief To ensure algorithmic integrity a process that has a 
             * shorter execution time but arrives later should not run before
             * a process that arrives earlier but with a longer execution time.
             * 
             * This constraint is enforced by adding the arrival time to the
             * execution time of a process when sorting.
             */
            return (
                first.getExecutionTime() + first.getArrivalTime() <
                second.getExecutionTime() + second.getArrivalTime()
            );
        }
    );
}

void IScheduler::randomizeProcessArrivalTime(void)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randTime = 0;

    for (size_t i = 0; i < this->processList->size(); ++i)
    {
        randTime = rand() % ( this->processList->size() + 1 );
        Process* p = &(this->processList->at(i));
        p->setArrivalTime(randTime);
    }
}

IScheduler::~IScheduler()
{
    if (this->processList != nullptr)
    {
        delete this->processList;
        this->processList = nullptr;
    }
}
