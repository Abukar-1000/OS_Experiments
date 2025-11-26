#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "../core/pipes/Pipe.h"

int main() {

   Pipe myPipe = Pipe()
                    .withPipeName("\\\\.\\pipe\\pipe1")
                    .withDesiredAccess(PIPE_ACCESS_DUPLEX)
                    .withMessageType(PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT)
                    .withDesiredInstances(2)
                    .withOutBufferSize(1024)
                    .withInBufferSize(1024)
                    .withDefaultTimeout(0)
                    .withConfiguration(Server)
                    .build();
    
    myPipe.waitForConnections();
    std::cout << "Client connected!\n";

    std::string msg = "Hello from server!";
    DWORD written;
    while (true) {
        myPipe.write<std::string>(msg);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    myPipe.close();
    return 0;
} 