#ifndef ExecutionMetric_Exists
#define ExecutionMetric_Exists
#include <iostream>
#include "../../process/Process.h"
#include <vector>

namespace metrics::scheduling
{
    class ExecutionMetric 
    {
        protected:
            size_t turnaroundTime;
            size_t responseTime;
            float turnaroundTimeFloat;
            float responseTimeFloat;
            std::string method;
            std::string turnaroundTimeAverage; 
            std::string responseTimeAverage;
            size_t processCount; 
        public:
            ExecutionMetric();
            void calculate(const std::vector<Process>* processes);
            std::string display(void);
    };
}
#endif 