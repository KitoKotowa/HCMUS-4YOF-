#include "syscall.h"

int main() {
    char buffer[] = "Hello, what's your name?";
    int bytesWritten;

    // Write to console output
    //bytesWritten = Write(buffer, sizeof(buffer) - 1, 1);
    //printf("Wrote %d bytes to console output\n", bytesWritten);

    // Write to file with OpenFileID 1
    int fileId = Open("abc.txt", 0);
    if (fileId >= 2 && fileId < 20) {
        bytesWritten = Write(buffer, sizeof(buffer) - 1, fileId);
        Close(fileId);
    }
    
    Halt();

    return 0;
}