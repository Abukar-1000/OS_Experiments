runA: pipe
	g++ -std=c++17 Pipe.o senderA.cpp -o senderA
	./senderA

runB: pipe
	g++ -std=c++17 Pipe.o senderB.cpp -o senderB
	./senderB

pipe:
	g++ -std=c++17 -g -c ..\core\pipes\Pipe.cpp -o Pipe.o

clean:
	rm *.o
	rm *.exe
	clear