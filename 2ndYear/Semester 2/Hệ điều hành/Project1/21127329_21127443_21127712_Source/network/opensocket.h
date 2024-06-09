#ifndef OPENSOCK_H_
#define OPENSOCK_H_

#include "sysdep.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

class OpenSock
{
public:
    OpenSock(int s)
    {
        socket = s;
        currentOffset = 0;
    }
    ~OpenSock() { CloseSocket(socket); }

    int Connect(char *ip, int port)
    {
        if (socket == -1)
            return -1;

        printf("%d\n", socket);
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_port = htons(port);

        if (connect(socket, (struct sockaddr *)&server, sizeof(server)) < 0)
            return -1;
        //cerr << "\nConnected by opensocket.h\n";
        return 0;
    }

    int Send(char *buffer, int len)
    {
        if (socket == -1)
            return -1;
        int cnt = send(socket, buffer, strlen(buffer), 0);
        if (cnt < 0)
            return -1;
        //cerr << "\nSent by opensocket.h\n";
        return cnt;
    }

    int Receive(char *buffer, int len)
    {
        if (socket == -1)
            return -1;
        int cnt = read(socket, buffer, len);
        if (cnt < 0)
            return -1;
        //cerr << "\nReceived by opensocket.h\n";
        return cnt;
    }

private:
    int socket;
    int currentOffset;
};

#endif OPENSOCK_H_