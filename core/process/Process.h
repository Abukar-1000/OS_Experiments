#ifndef Process_EXISTS
#define Process_EXISTS
#include <cstddef>

class Process {
    protected:
        size_t executionTime;
        size_t completionTime;
        size_t firstRunTime;
        size_t elapsedTime;
        int executionTimeUpperBound; // Optionally limits the random process execution time to an upper bound.
    public:
        Process();
        Process(size_t time);
        Process(Process&& other);
        Process(const Process& other);
        Process& operator= (const Process& other);
        void withExecutionTimeUpperBound(int bound);
        void setCompletionTime(size_t time);
        void setFirstRunTime(size_t time);
        size_t getCompletionTime(void);
        size_t getFirstRunTime(void);
        size_t getElapsedTime(void);
        bool isComplete(void);
        bool hasRun(void);
        void run(size_t time);
};

#endif