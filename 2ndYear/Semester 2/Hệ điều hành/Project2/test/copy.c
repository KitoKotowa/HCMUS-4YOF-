#include "syscall.h"

#define READWRITE 0
#define READONLY 1

int main() {
    char buffer[1023];
    char filename1[255];
    char filename2[255];
    int id1;
    int id2;
    int result = -1;
    int bytesRead;

    //PrintString("Type source file: ");
    //Read(filename1, sizeof(filename1), 0);
    //PrintString("Type destination file: ");
    //Read(filename2, sizeof(filename2), 0);
    id1 = Open("abc.txt", READWRITE);

    if (id1 != -1){
        id2 = Open("123.txt", READWRITE);
        bytesRead = Read(buffer, sizeof(buffer), id1);
        if (id2 == -1)
        {
            CreateFile(filename2);
            id2 = Open(filename2, READWRITE);
        }
        result = Write(buffer, bytesRead, id2);
        Close(id1);
    }
    if (result != -1)
    {
        //Write("\nSuccessfully copy file '", sizeof("Successfully copy file '"), 1);
        //Write(filename1, sizeof(filename1), 1);
        //Write("' to file '", sizeof("' to file '"), 1);
        //Write(filename2, sizeof(filename2), 1);
        //Write("'\n", sizeof("'\n"), 1);
        Close(id2);
    }

    //Halt();
}