#include "syscall.h"
#include "copyright.h"

#define READWRITE 0
#define READONLY 1

int main() {
    char buffer[1023];
    char filename1[255];
    char filename2[255];
    int id1, id2, newPos, bytesRead;
    int pos = -1;
    int result = -1;
    PrintString("Type file name 1: ");
    Read(filename1, sizeof(filename1), 0);
    PrintString("Type file name 2: ");
    Read(filename2, sizeof(filename2), 0);
    id1 = Open(filename1, READWRITE);
    id2 = Open(filename2, READWRITE);

    if (id1 != -1 && id2 != -1){
        newPos = Seek(pos, id1);
        if (newPos != -1)
        {
            bytesRead = Read(buffer, sizeof(buffer), id2);
            result = Write(buffer, bytesRead, id1);
        }

        else{
            PrintString("\nError: Cannot seek\n");
        }
    }

    if (result != -1){
        PrintString("\nSuccessfully concatenate file '");
        PrintString(filename2);
        PrintString("' to file '");
        PrintString(filename1);
        PrintString("'\n");
    }
    Close(id1);
    Close(id2);

    Halt();
}