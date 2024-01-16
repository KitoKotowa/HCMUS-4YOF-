#include "syscall.h"
#include "copyright.h"

int main() {
    // use fileName variable here
    char filename[255];
    int id;
    PrintString("Type file name to create: ");
    Read(filename, sizeof(filename), 0);
    id = Create(filename);
    if (id != -1){
        PrintString("Successfully create file '");
        PrintString(filename);
        PrintString("'.\n");
    }
    Halt();
    return 0;
}