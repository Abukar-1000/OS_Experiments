#include "ExecutionMetric.h"
#include <string>

namespace metrics::scheduling
{
    ExecutionMetric::ExecutionMetric()
    :   turnaroundTime(0),
        responseTime(0),
        processCount(0),
        turnaroundTimeAverage(""),
        responseTimeAverage("")
    {}

    void ExecutionMetric::calculate(const std::vector<Process>* processList)
    {
        this->processCount = processList->size();
        for (size_t i = 0; i < processList->size(); ++i)
        {
            Process p = processList->at(i);
            this->turnaroundTime += p.getCompletionTime();
            this->responseTime += p.getFirstRunTime();
            std::cout << i << ":\t" << "( " << p.getFirstRunTime() << ", " << p.getCompletionTime() << " )\n";
        }

        this->turnaroundTimeAverage += std::to_string(this->turnaroundTime) + "/" + std::to_string(this->processCount);
        this->responseTimeAverage += std::to_string(this->responseTime) + "/" + std::to_string(this->processCount);
        
        this->turnaroundTimeFloat = (float) (this->turnaroundTime / this->processCount);
        this->responseTimeFloat = (float) (this->responseTime / this->processCount);
    }

    std::string ExecutionMetric::display(void)
    {
        std::string metrics = this->method + "\t Turnaround Time: " + this->turnaroundTimeAverage + " = " + std::to_string(this->turnaroundTimeFloat);
        metrics += "\t Response Time: " + this->responseTimeAverage + " = " + std::to_string(this->responseTimeFloat);
        return metrics;
    }
}