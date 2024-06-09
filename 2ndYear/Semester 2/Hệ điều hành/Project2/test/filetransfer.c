#include "syscall.h"
#include "copyright.h"

int main(){
    char *file1 = "abc.txt";
    char *file2 = "123.txt";
    //char file1[255];
    //char file2[255];
    int fileId1, fileId2, id, bytesRead, bytesWritten;
    char *ip = "127.0.0.1";
    int port = 8080;
    char buffer[1024];
    char receivedBuffer[1024];

    //PrintString("Enter source file name: ");
    //Read(file1, sizeof(file1), 0);
    //PrintString("Enter destination file name: ");
    //Read(file2, sizeof(file2), 0);

    PrintString("\nStart\n");

    fileId1 = Open(file1, 0);
    if (fileId1 >= 2 && fileId1 < 20) {
        bytesRead = Read(buffer, sizeof(buffer), fileId1);
        PrintString("Read buffer: ");
        PrintString(buffer);
        PrintString("\n");
        Close(fileId1);
    }

    PrintString("File read");
    PrintString("\n");

    id = SocketTCP();
    Connect(id,ip,port);
    Write(buffer,sizeof(buffer),id);
    bytesRead = Read(receivedBuffer, sizeof(receivedBuffer), id);
    Write(receivedBuffer, bytesRead, 1);
    PrintString("\n");
    PrintString("Echo");
    PrintString("\n");


    fileId2 = Open(file2, 0);
    if (fileId2 >= 2 && fileId2 < 20) {
        bytesWritten = Write(receivedBuffer, sizeof(receivedBuffer) - 1, fileId2);
        Close(fileId2);
    }

    PrintString("File written");
    PrintString("\n");

    Halt();
    return 0;
}