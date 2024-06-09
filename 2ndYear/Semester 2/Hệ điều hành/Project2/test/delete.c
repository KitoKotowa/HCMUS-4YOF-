#include "syscall.h"

#define READWRITE 0
#define READONLY 1

int main() {
    char filename[255];
    int result = -1;
    PrintString("File name to delete: ");
    Read(filename, sizeof(filename), 0);
    result = Remove(filename);

    if (result != -1){
        PrintString("Successfully delete file '");
        PrintString(filename);
        PrintString("'\n");
    }

    Halt();
}