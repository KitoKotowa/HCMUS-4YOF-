#ifndef SOCKETSYS_H
#define SOCKETSYS_H

#include "filesys.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

class Socket
{
public:
    FileSystem *fileSys;
    Socket() { fileSys = new FileSystem; }
    ~Socket() { delete fileSys; }

    int SocketTCP()
    {
        return fileSys->AppendSocket();
    }

    int Connect(int socketid, char *ip, int port)
    {
        if (socketid == -1)
            return -1;

        struct sockaddr_in server;
        int len = sizeof(server);

        memset(&server, '0', len);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if (inet_pton(AF_INET, ip, &server.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(socketid, (struct sockaddr *)&server, len) < 0)
        {
            printf("\nConnection failed \n");
            return -1;
        }
        cerr << "\nConnected in socketSys.h";
        return 0;
    }

    int Send(int socketid, char *buffer, int len)
    {
        int cnt;

        if (socketid == -1)
            return -1;
        cnt = send(socketid, buffer, strlen(buffer), 0);
        if (cnt < 0)
            return -1;
        cerr << "\nSent in socketSys.h\n";
        return cnt;
    }

    int Receive(int socketid, char *buffer, int len)
    {
        int cnt;

        if (socketid == -1)
            return -1;
        memset(buffer, 0, sizeof(buffer));
        cnt = read(socketid, buffer, len);
        printf("%s\n", buffer);
        printf("%d\n", cnt);
        if (cnt < 0)
            return -1;
        cerr << "\nReceived in socketSys.h\n";
        return cnt;
    }

    int CloseSocket(int socketid)
    {
        return fileSys->RemoveSocket(socketid);
    }
};

#endif SOCKETSYS_H