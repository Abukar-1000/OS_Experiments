main: FIFO SJF RoundRobin
	g++ -std=c++17 -g Process.o ExecutionMetric.o IScheduler.o FIFO.o SJF.o RoundRobin.o main.cpp -o schedulingEx
	./schedulingEx

RoundRobin: ISchedule
	g++ -std=c++17 -g -c IScheduler.o ..\core\scheduling\RoundRobin.cpp -o RoundRobin.o

SJF: ISchedule
	g++ -std=c++17 -g -c IScheduler.o ..\core\scheduling\SJF.cpp -o SJF.o

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