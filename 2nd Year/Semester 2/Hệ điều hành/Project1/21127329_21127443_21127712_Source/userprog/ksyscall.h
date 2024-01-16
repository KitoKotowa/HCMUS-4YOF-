/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysSocketTCP()
{
  int socketID = kernel->fileSystem->AppendSocket();
  if (socketID == -1)
  {
    DEBUG(dbgSys, "\nFailed to open socket!");
    return -1;
  }

  DEBUG(dbgSys, "\nOpen socket successfully!");
  return socketID;
}

int SysConnect(int socketid, char *ip, int port)
{
  int connected = kernel->fileSystem->FilePtr[socketid]->Connect(ip, port);

  if (connected == -1)
  {
    DEBUG(dbgSys, "\nFailed to connect socket!");
    return -1;
  }

  DEBUG(dbgSys, "\nConnect to socket successfully!");
  return 0;
}

int SysSend(int socketid, char *buffer, int len, int connection)
{
  if (connection == -1)
  {
    DEBUG(dbgSys, "\nConnection is closed!");
    return 0;
  }

  int sent = kernel->fileSystem->FilePtr[socketid]->Send(buffer, len);
  if (sent == -1)
  {
    DEBUG(dbgSys, "\nFailed to send data to socket!");
    return -1;
  }

  DEBUG(dbgSys, "\nSend data to socket successfully!");
  return sent;
}

int SysReceive(int socketid, char *buffer, int len, int connection)
{
  if (connection == -1)
  {
    DEBUG(dbgSys, "\nConnection is closed!");
    return 0;
  }

  int received = kernel->fileSystem->FilePtr[socketid]->Receive(buffer, len);
  if (received == -1)
  {
    DEBUG(dbgSys, "\nFailed to receive data from socket!");
    return -1;
  }

  DEBUG(dbgSys, "\nReceive data from socket successfully!");
  return received;
}

int SysCloseSocket(int socketid)
{
  if (socketid == -1)
  {
    DEBUG(dbgSys, "\nFailed to close socket!");
    return -1;
  }
  int close = kernel->fileSystem->RemoveSocket(socketid);
  if (close == -1)
  {
    DEBUG(dbgSys, "\nFailed to close socket!");
    return -1;
  }
  DEBUG(dbgSys, "\nClose socket successfully!");
  return 0;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
