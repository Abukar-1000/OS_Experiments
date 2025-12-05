#include <iostream>
#include "../core/scheduling/FIFO.h"
#include "../core/scheduling/SJF.h"
#include "../core/scheduling/RoundRobin.h"
#define LINE_BREAK() std::cout << "\n\n\n"

int main()
{
    const size_t PROCESS_COUNT = 10;

    FIFO fifo = FIFO(PROCESS_COUNT);
    fifo.run();
    fifo.displayMetrics();    
    
    LINE_BREAK();

    SJF sjf = SJF(PROCESS_COUNT);
    sjf.run();
    sjf.displayMetrics();
    
    LINE_BREAK();

    RoundRobin RR = RoundRobin(PROCESS_COUNT);
    RR.setQuantum(100);
    RR.run();
    RR.displayMetrics();

    return 0;
}