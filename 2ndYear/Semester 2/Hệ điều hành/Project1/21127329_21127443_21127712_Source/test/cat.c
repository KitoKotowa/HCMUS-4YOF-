#include "syscall.h"

#define READWRITE 0
#define READONLY 1

int main() {
    char buffer[1023];
    char filename[255];
    int id;
    int result = -1;

    PrintString("File name: ");
    Read(filename, sizeof(filename), 0);
    id = Open(filename, READWRITE);

    if (id != -1){
        result = Read(buffer, sizeof(buffer), id);
    }

    if (result != -1){
        PrintString("\n'");
        PrintString(filename);
        PrintString("': \n");
        Write(buffer, result, 1);
        PrintString("\n");
    }
    Close(id);

    Halt();
}