#ifndef Pipe_h_EXISTS
#define Pipe_h_EXISTS
#include <Windows.h>

enum User {
    Server,
    Client
};

class Pipe {
    protected:
        HANDLE handle;
        size_t clientCount;
        size_t readBufferSize;
        LPCSTR fileName;
        DWORD desiredAccess;
        DWORD messageType;
        DWORD desiredInstances;
        DWORD shareMode;
        LPSECURITY_ATTRIBUTES security;
        DWORD creationDisposition;
        DWORD falgsAndAttributes;
        HANDLE templateFile;
        DWORD inBufferSize;
        DWORD outBufferSize;
        DWORD defaultTimeout;
        User configurationType;
    public:
        Pipe();  
        ~Pipe();  
        Pipe& withPipeName(LPCSTR fileName);
        Pipe& withDesiredAccess(DWORD access);
        Pipe& withMessageType(DWORD messageType);
        Pipe& withDesiredInstances(DWORD desiredInstances);
        Pipe& withShareMode(DWORD shareMode);
        Pipe& withSecurity(LPSECURITY_ATTRIBUTES security);
        Pipe& withCreationDisposition(DWORD creationDisposition);
        Pipe& withFlagsAndAttributes(DWORD falgsAndAttributes);
        Pipe& withTemplateFile(HANDLE templateFile);
        Pipe& withConfiguration(User user);
        Pipe& withInBufferSize(DWORD inBufferSize);
        Pipe& withOutBufferSize(DWORD outBufferSize);
        Pipe& withDefaultTimeout(DWORD defaultTimeout);
        bool waitForConnections(void);
        Pipe& build(void);
        
        template<typename T>
        bool write(T data);
        
        template<typename K>
        K read(void);
        
        void close(void);
};
#endif