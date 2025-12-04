#include "Process.h"
#include <ctime>
#include<iostream>

Process::Process()
:   executionTimeUpperBound(100000),
    completionTime(NULL),
    firstRunTime(NULL),
    elapsedTime(0)
{
    this->executionTime = rand() % this->executionTimeUpperBound;
}

Process::Process(size_t time)
:   executionTimeUpperBound(time + 1),
    completionTime(NULL),
    firstRunTime(NULL),
    executionTime(time),
    elapsedTime(0)
{}

Process::Process(Process&& other)
{
    this->completionTime = other.completionTime;
    this->executionTime = other.executionTime;
    this->firstRunTime = other.firstRunTime;
    this->elapsedTime = other.elapsedTime;
}

Process::Process(const Process& other)
{
    this->completionTime = other.completionTime;
    this->executionTime = other.executionTime;
    this->firstRunTime = other.firstRunTime;
    this->elapsedTime = other.elapsedTime;
}

Process& Process::operator= (const Process& other)
{
    this->completionTime = other.completionTime;
    this->executionTime = other.executionTime;
    this->firstRunTime = other.firstRunTime;
    this->elapsedTime = other.elapsedTime;
    
    return *this;
}

bool Process::isComplete(void)
{
    return this->executionTime == 0;
}

bool Process::hasRun(void)
{
    return this->firstRunTime != NULL;
}

void Process::setFirstRunTime(size_t time)
{
    this->firstRunTime = time;
}

void Process::setCompletionTime(size_t time)
{
    this->completionTime = time;
}

void Process::withExecutionTimeUpperBound(int bound)
{
    this->executionTimeUpperBound = bound;
    if (this->executionTime >= this->executionTimeUpperBound)
    {
        this->executionTime = this->executionTime % this->executionTimeUpperBound;
    }
}

size_t Process::getFirstRunTime(void)
{
    return this->firstRunTime;
}

size_t Process::getCompletionTime(void)
{
    return this->completionTime;
}

size_t Process::getElapsedTime(void)
{
    return this->elapsedTime;
}

void Process::run(size_t time)
{
    const size_t OVERFLOW_THRESH = 18446744073709551610;
    bool isUnderflow = (this->executionTime - time) >= OVERFLOW_THRESH;
    if (isUnderflow) 
    {
        this->executionTime = 0;
        return;
    }
    
    this->executionTime -= time;
    this->elapsedTime += time;
    
}