#include "syscall.h"
#include "copyright.h"

int main() {
    char buffer[1024];
    char blank[1024];
    char *mess1 = "Hello from the other sideeeeeee";
    char *mess2 = "message of the second socket";
    char *mess3 = "message of the third socket";
    char *mess4 = "message of the fourth socket";
    int id1, id2, id3, id4;
    int byte;

    id1 = SocketTCP();
    Connect(id1, "127.0.0.1", 8080);
    Write(mess1, 1024, id1);
    byte = Read(buffer, sizeof(buffer), id1);
    Write(buffer, byte, 1);
    PrintString("\n");
    CloseSock(id1);
    
    PrintString("\nEnter to proceed the next socket connection...\n");
    Read(blank,sizeof(blank),0);

    id2 = SocketTCP();
    Connect(id2, "127.0.0.1", 8080);
    Write(mess2, 1024, id2);
    byte = Read(buffer, sizeof(buffer), id2);
    Write(buffer, byte, 1);
    PrintString("\n");
    CloseSock(id2);

    PrintString("\nEnter to proceed the next socket connection...\n");
    Read(blank,sizeof(blank),0);

    id3 = SocketTCP();
    Connect(id3, "127.0.0.1", 8080);
    Write(mess3, 1024, id3);
    byte = Read(buffer, sizeof(buffer), id3);
    Write(buffer, byte, 1);
    PrintString("\n");
    CloseSock(id3);

    PrintString("\nEnter to proceed the next socket connection...\n");
    Read(blank,sizeof(blank),0);

    id4 = SocketTCP();
    Connect(id4, "127.0.0.1", 8080);
    Write(mess4, 1024, id4);
    byte = Read(buffer, sizeof(buffer), id4);
    Write(buffer, byte, 1);
    PrintString("\n");
    CloseSock(id4);

    Halt();
    return 0;
}