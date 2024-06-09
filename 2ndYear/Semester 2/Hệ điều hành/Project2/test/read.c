#include "syscall.h"

int main() {
    char buffer[1024];
    int bytesRead;

    // Read from console input
    // bytesRead = Read(buffer, sizeof(buffer), 0);

    // Read from file with OpenFileID 1
    int fileId = Open("abc.txt", 1);
    if (fileId >= 2 && fileId < 20) {
        bytesRead = Read(buffer, sizeof(buffer), fileId);
        PrintString("Number of bytes read: ");
        PrintInt(bytesRead);
        Close(fileId);
    }
    

    Halt();

    return 0;
}