#include "IScheduler.h"
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

IScheduler::~IScheduler()
{
    if (this->processList != nullptr)
    {
        delete this->processList;
        this->processList = nullptr;
    }
}

void IScheduler::displayMetrics(void)
{
    metrics::scheduling::ExecutionMetric _metrics = metrics::scheduling::ExecutionMetric();
    _metrics.calculate(this->processList);
    std::cout <<  _metrics.display() << "\n";
}