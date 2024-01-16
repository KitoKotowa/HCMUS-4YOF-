#include "syscall.h"

int main() {
    int fileId;
    int pos = 8;
    int newPos;
    char c;

    fileId = Open("abc.txt", 1);
    if (fileId == -1) {
        PrintString("Error: Could not open file\n");
        return 1;
    }

    newPos = Seek(pos, fileId);
    if (newPos == -1) {
        PrintString("Error: Could not seek\n");
        return 1;
    }

    PrintString("The seek position is: ");
    PrintInt(newPos);
    PrintString("\nThe character is: ");
    ReadCharAt(&c, 1, fileId);

    Close(fileId);
    Halt();

    return 0;
}