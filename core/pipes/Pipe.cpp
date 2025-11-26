#include "Pipe.h"
#include <iostream>
#include <type_traits>

Pipe::Pipe()
:   handle(NULL),
    clientCount(0),
    readBufferSize(128),
    inBufferSize(1024),
    outBufferSize(1024),
    defaultTimeout(0),
    security(NULL),
    templateFile(NULL)
{}

Pipe& Pipe::build(void)
{
    if (this->configurationType == Server)
    {
        this->handle = CreateNamedPipeA(
            this->fileName,
            this->desiredAccess,
            this->messageType,
            this->desiredInstances,
            this->outBufferSize,
            this->inBufferSize,
            this->defaultTimeout,
            this->security
        );

        if (this->handle == INVALID_HANDLE_VALUE) {        
            std::cerr << "CreateNamedPipeA failed. Error:" << GetLastError() << "\n";
            throw std::runtime_error("Failed to initialize Pipe.");
        }
    }

    else if (this->configurationType == Client) {
        this->handle = CreateFileA(
            this->fileName,
            this->desiredAccess,
            this->shareMode,
            this->security,
            this->creationDisposition,
            this->falgsAndAttributes,
            this->templateFile
        );

        if (this->handle == INVALID_HANDLE_VALUE) {        
            std::cerr << "CreateFile failed. Error:" << GetLastError() << "\n";
            throw std::runtime_error("Failed to initialize Pipe.");
        }
    }
    else {
        throw std::runtime_error("Unknown configuration, call withConfiguration() with wither Server or Client.");
    }

    return *this;
}

template<typename K>
K Pipe::read(void)
{
    if constexpr (std::is_same_v<K, std::string>) {
        char buffer[this->inBufferSize];
        memset(buffer, 0, this->inBufferSize);
        
        DWORD bytesRead;
        bool success = ReadFile(this->handle, buffer, sizeof(buffer), &bytesRead, NULL);
        
        if (!success) {
            throw std::runtime_error("Failed to read from Pipe.");
        }
        
        std::string value(buffer, sizeof(buffer));
        return value;
    } 
    else {
        K value;
        DWORD bytesRead;
        bool success = ReadFile(this->handle, &value, sizeof(K), &bytesRead, NULL);
        
        if (!success) {
            throw std::runtime_error("Failed to read from Pipe.");
        }

        return value;
    }
}

template<typename T>
bool Pipe::write(T value)
{
    DWORD written;
    if constexpr (std::is_same_v<T, std::string>)
    {
        const char* buffer = value.c_str();
        WriteFile(this->handle, buffer, value.size(), &written, NULL);
    }
    else {
        WriteFile(this->handle, &value, sizeof(T), &written, NULL);
    }
    return 0;
}

Pipe& Pipe::withConfiguration(User user)
{
    this->configurationType = user;
    return *this;
}

Pipe& Pipe::withPipeName(LPCSTR fileName)
{
    this->fileName = fileName;
    return *this;
}

Pipe& Pipe::withDesiredAccess(DWORD access)
{
    this->desiredAccess = access;
    return *this;
}

Pipe& Pipe::withMessageType(DWORD messageType)
{
    this->messageType = messageType;
    return *this;
}

Pipe& Pipe::withDesiredInstances(DWORD desiredInstances)
{
    this->desiredInstances = desiredInstances;
    return *this;
}

Pipe& Pipe::withShareMode(DWORD shareMode)
{
    this->shareMode = shareMode;
    return *this;
}

Pipe& Pipe::withSecurity(LPSECURITY_ATTRIBUTES security)
{
    this->security = security;
    return *this;
}

Pipe& Pipe::withCreationDisposition(DWORD creationDisposition)
{
    this->creationDisposition = creationDisposition;
    return *this;
}

Pipe& Pipe::withFlagsAndAttributes(DWORD flagsAndAttributes)
{
    this->falgsAndAttributes = flagsAndAttributes;
    return *this;
}

Pipe& Pipe::withTemplateFile(HANDLE templateFile)
{
    this->templateFile = templateFile;
    return *this;
}

Pipe& Pipe::withInBufferSize(DWORD inBufferSize)
{
    this->inBufferSize = inBufferSize;
    return *this;
}

Pipe& Pipe::withOutBufferSize(DWORD outBufferSize)
{
    this->outBufferSize = outBufferSize;
    return *this;
}

Pipe& Pipe::withDefaultTimeout(DWORD defaultTimeout)
{
    this->defaultTimeout = defaultTimeout;
    return *this;
}

bool Pipe::waitForConnections(void)
{
    BOOL success = ConnectNamedPipe(this->handle, NULL);
    
    if (success)
    {
        return true;
    }

    DWORD err = GetLastError();
    if (err == ERROR_PIPE_CONNECTED)
    {
        std::cout << "Client already connected\n";
        return true;
    }

    if (err == ERROR_IO_PENDING)
    {
        std::cout << "Pending I/O opperation\n";
        return true;
    }

    std::cerr << " Listening for connections failed. Error: " << err << "\n"; 
    throw std::runtime_error("");

}

Pipe::~Pipe()
{}

void Pipe::close(void)
{
    CloseHandle(this->handle);
}

template bool Pipe::write<int>(int);
template bool Pipe::write<float>(float);
template bool Pipe::write<double>(double);
template bool Pipe::write<std::string>(std::string);


template int Pipe::read<int>(void);
template float Pipe::read<float>(void);
template double Pipe::read<double>(void);
template std::string Pipe::read<std::string>(void);