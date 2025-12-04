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
            this->turnaroundTime += ( p.getCompletionTime() - p.getArrivalTime());
            this->responseTime += ( p.getFirstRunTime() - p.getArrivalTime() );
            std::cout << i 
                << " " 
                << " [" << p.getArrivalTime() << "]" << ": " 
                << "( " << p.getFirstRunTime() << ", " << p.getCompletionTime() << " )"
                << "\t\tExecution Time:\t"
                << p.getElapsedTime()
                << "\n";
        }

        this->turnaroundTimeAverage += std::to_string(this->turnaroundTime) + "/" + std::to_string(this->processCount);
        this->responseTimeAverage += std::to_string(this->responseTime) + "/" + std::to_string(this->processCount);
        
        this->turnaroundTimeFloat = (float) (this->turnaroundTime / this->processCount);
        this->responseTimeFloat = (float) (this->responseTime / this->processCount);
    }

    std::string ExecutionMetric::display(void)
    {
        std::string metrics = this->method + "\n\n Turnaround Time: " + this->turnaroundTimeAverage + " = " + std::to_string(this->turnaroundTimeFloat);
        metrics += "\t Response Time: " + this->responseTimeAverage + " = " + std::to_string(this->responseTimeFloat);
        return metrics;
    }
}