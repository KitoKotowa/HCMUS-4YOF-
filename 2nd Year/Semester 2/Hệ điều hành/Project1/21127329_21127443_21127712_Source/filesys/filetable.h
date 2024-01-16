// #include "openfile.h"
// #include "sysdep.h"
// #include "opensocket.h"

// #define TABLE_SIZE 20
// #define TYPE_READWRITE 0
// #define TYPE_READ 1
// #define IS_SOCKET 3
// #define IS_FILE 4

// struct Table
// {
//     int type;
//     union
//     {
//         OpenSock *socket;
//         OpenFile *file;
//     };
// };

// class FileTable
// {
// public:
//     FileTable()
//     {
//         openT = new Table *[TABLE_SIZE];
//         for (int i = 0; i < TABLE_SIZE; ++i)
//             openT[i] = NULL;
//     }

//     int AppendSocket()
//     {
//         int freeSlot = -1;
//         int descriptor = -1;
//         for (int i = 2; i < TABLE_SIZE; ++i)
//         {
//             if (openT[i] == NULL)
//             {
//                 freeSlot = i;
//                 break;
//             }
//         }

//         if (freeSlot == -1)
//             return -1;

//         descriptor = socket(AF_INET, SOCK_STREAM, 0);
//         if (descriptor == -1)
//             return -1;

//         openT[freeSlot] = new Table;
//         openT[freeSlot]->type = IS_SOCKET;
//         openT[freeSlot]->socket = new OpenSock(descriptor);
//         return freeSlot;
//     }

//     int AppendFile(char *fileName, int openType)
//     {
//         int freeSlot = -1;
//         int fileDescriptor = -1;
//         for (int i = 2; i < TABLE_SIZE; ++i)
//         {
//             if (openT[i] == NULL)
//             {
//                 freeSlot = i;
//                 break;
//             }
//         }

//         if (freeSlot == -1)
//             return -1;

//         if (openType == TYPE_READWRITE)
//             fileDescriptor = OpenForReadWrite(fileName, FALSE);
//         else if (openType == TYPE_READ)
//             fileDescriptor = OpenForRead(fileName, FALSE);

//         if (fileDescriptor == -1)
//             return -1;

//         openT[freeSlot] = new Table;
//         openT[freeSlot]->type = IS_FILE;
//         openT[freeSlot]->file = new OpenFile(fileDescriptor);
//         return freeSlot;
//     }

//     int Remove(int id)
//     {
//         if (id < 2 || id >= TABLE_SIZE)
//             return -1;
//         if (openT[id])
//         {
//             if (openT[id]->type == IS_FILE)
//                 delete openT[id]->file;
//             else if (openT[id]->type == IS_SOCKET)
//                 delete openT[id]->socket;
//             delete openT[id];
//             openT[id] = NULL;
//             return 0;
//         }
//         return -1;
//     }

//     ~FileTable()
//     {
//         for (int i = 0; i < TABLE_SIZE; ++i)
//             if (openT[i])
//                 delete openT[i];
//         delete[] openT;
//     }

// private:
//     Table **openT;
// };