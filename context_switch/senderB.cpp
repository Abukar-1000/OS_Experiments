#include <iostream>
#include <Windows.h>
#include "../core/pipes/Pipe.h"

int main() {
    
    Pipe myPipe = Pipe()
                    .withPipeName("\\\\.\\pipe\\pipe1")
                    .withDesiredAccess(GENERIC_READ | GENERIC_WRITE)
                    .withShareMode(0)
                    .withCreationDisposition(OPEN_EXISTING)
                    .withFlagsAndAttributes(0)
                    .withConfiguration(Client)
                    .build();
    
    
    std::string msg = "";
    while (true) {
        msg = myPipe.read<std::string>();    
        std::cout << "Server says: " << msg << "\n";
    }

    myPipe.close();
    return 0;
} 