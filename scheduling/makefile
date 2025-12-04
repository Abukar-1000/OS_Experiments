main: FIFO 
	g++ -std=c++17 Process.o ExecutionMetric.o IScheduler.o FIFO.o main.cpp -o schedulingEx
	./schedulingEx

FIFO: ISchedule
	g++ -std=c++17 -g -c IScheduler.o ..\core\scheduling\FIFO.cpp -o FIFO.o

ISchedule: ExecutionMetric Process
	g++ -std=c++17 -g -c Process.o ExecutionMetric.o ..\core\scheduling\IScheduler.cpp -o IScheduler.o

ExecutionMetric: Process
	g++ -std=c++17 -g -c Process.o ..\core\metrics\scheduling\ExecutionMetric.cpp -o ExecutionMetric.o

Process:
	g++ -std=c++17 -g -c ..\core\process\Process.cpp -o Process.o

clean:
	rm *.o
	rm schedulingEx
	clear