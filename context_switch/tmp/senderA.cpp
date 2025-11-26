#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

int main() {

    HANDLE hPipe = CreateNamedPipeA(
        "\\\\.\\pipe\\pipe1",
        PIPE_ACCESS_DUPLEX,          // read + write
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,                           // max instances
        1024,                        // out buffer
        1024,                        // in buffer
        0,                           // default timeout
        NULL                         // security attributes
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateNamedPipe failed: " << GetLastError() << "\n";
        return 1;
    }

    std::cout << "Waiting for client...\n";
    ConnectNamedPipe(hPipe, NULL);  // blocks until client connects

    std::cout << "Client connected!\n";

    const char* msg = "Hello from server!";
    DWORD written;

    while (true) {
        WriteFile(hPipe, msg, strlen(msg), &written, NULL);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    CloseHandle(hPipe);
    
} 