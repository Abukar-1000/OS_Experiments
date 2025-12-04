#include "../core/scheduling/FIFO.h"

int main()
{
    FIFO fifo = FIFO(10);
    fifo.run();
    fifo.displayMetrics();    
    return 0;
}