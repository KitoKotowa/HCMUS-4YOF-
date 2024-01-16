// filesys.h
//	Data structures to represent the Nachos file system.
//
//	A file system is a set of files stored on disk, organized
//	into directories.  Operations on the file system have to
//	do with "naming" -- creating, opening, and deleting files,
//	given a textual file name.  Operations on an individual
//	"open" file (read, write, close) are to be found in the Table
//	class (Table.h).
//
//	We define two separate implementations of the file system.
//	The "STUB" version just re-defines the Nachos file system
//	operations as operations on the native UNIX file system on the machine
//	running the Nachos simulation.
//
//	The other version is a "real" file system, built on top of
//	a disk simulator.  The disk is simulated using the native UNIX
//	file system (in a file named "DISK").
//
//	In the "real" implementation, there are two key data structures used
//	in the file system.  There is a single "root" directory, listing
//	all of the files in the file system; unlike UNIX, the baseline
//	system does not provide a hierarchical directory structure.
//	In addition, there is a bitmap for allocating
//	disk sectors.  Both the root directory and the bitmap are themselves
//	stored as files in the Nachos file system -- this causes an interesting
//	bootstrap problem when the simulated disk is initialized.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef FS_H
#define FS_H

#include "copyright.h"
#include "sysdep.h"
#include "openfile.h"
#include "opensocket.h"

#define READWRITE 0
#define READONLY 1
#define STD_IN 2
#define STD_OUT 3
#define IS_SOCKET 4
#define TABLE_SIZE 20

// struct Table
// {
// 	int type;
// 	union
// 	{
// 		OpenSock *socket;
// 		OpenFile *file;
// 	};
// };

#ifdef FILESYS_STUB // Temporarily implement file system calls as
// calls to UNIX, until the real file system
// implementation is available
class FileSystem
{

public:
	OpenFile **FilePtr;

	FileSystem()
	{
		FilePtr = new OpenFile *[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; ++i)
			FilePtr[i] = NULL;

		this->Create("stdin", 0);
		this->Create("stdout", 0);

		FilePtr[0] = this->Open("stdin", STD_IN);
		FilePtr[1] = this->Open("stdout", STD_OUT);
	}

	~FileSystem()
	{
		for (int i = 0; i < TABLE_SIZE; ++i)
			if (FilePtr[i])
				delete FilePtr[i];
		delete[] FilePtr;
	}

	bool Create(char *name, int initialSize)
	{
		int fileDescriptor = OpenForWrite(name);

		if (fileDescriptor == -1)
			return FALSE;
		return true;
	}

	int AppendSocket()
	{
		int descriptor = -1;
		int freeSlot = BlankSpace();

		if (freeSlot == -1)
			return -1;

		descriptor = socket(AF_INET, SOCK_STREAM, 0);
		if (descriptor == -1)
			return -1;

		FilePtr[freeSlot] = new OpenFile(descriptor, IS_SOCKET);
		//cerr << "\nSocket appended in fileSys.h\n";
		//cerr << "\nfile index: " << freeSlot << "\n";
		return freeSlot;
	}

	OpenFile *Open(char *name)
	{
		int fileDescriptor = OpenForReadWrite(name, FALSE);

		if (fileDescriptor == -1)
			return NULL;

		return new OpenFile(fileDescriptor, name);
	}

	OpenFile *Open(char *name, int t)
	{
		int fileDescriptor = OpenForReadWrite(name, FALSE);

		if (fileDescriptor == -1)
			return NULL;

		return new OpenFile(fileDescriptor, name, t);
	}

	int AppendFile(char *name)
	{
		int fileDescriptor = -1;
		int freeSlot = BlankSpace();

		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			printf("%d ", FilePtr[i] == NULL);
		}

		if (freeSlot == -1)
		{
			printf("Error: There is not enough space.\n");
			return -1;
		}

		fileDescriptor = OpenForReadWrite(name, FALSE);

		if (fileDescriptor == -1)
		{
			printf("Error: File not found.\n");
			return -1;
		}

		FilePtr[freeSlot] = new OpenFile(fileDescriptor, name, 0);
		return freeSlot;
	}

	int AppendFile(char *name, int t)
	{

		int fileDescriptor = -1;
		int freeSlot = BlankSpace();

		if (freeSlot == -1)
		{
			printf("Error: There is not enough space.\n");
			return -1;
		}

		fileDescriptor = OpenForReadWrite(name, FALSE);

		if (fileDescriptor == -1)
		{
			printf("Error: File not found.\n");
			return -1;
		}

		FilePtr[freeSlot] = new OpenFile(fileDescriptor, name, t);

		return freeSlot;
	}

	int BlankSpace()
	{
		for (int i = 2; i < TABLE_SIZE; i++)
		{
			if (FilePtr[i] == NULL)
				return i;
		}
		return -1;
	}

	bool CheckOpenFile(int fileId)
	{
		if (fileId < 0 || fileId >= TABLE_SIZE)
			return false;
		if (FilePtr[fileId] == NULL)
			return false;
		return true;
	}

	int Seek(int pos, int id)
	{
		if (FilePtr[id]->type == IS_SOCKET)
		{
			printf("Error: Cannot seek socket.\n");
			return -1;
		}
		if (id < 0 || id >= TABLE_SIZE || FilePtr[id] == NULL)
		{
			printf("Error: invalid file ID");
			return -1;
		}

		if (FilePtr[id]->type == STD_IN || FilePtr[id]->type == STD_OUT)
		{
			printf("Error: cannot seek on console I/O");
			return -1;
		}

		int length = FilePtr[id]->Length();
		int newPos;

		if (pos == -1)
		{
			newPos = length;
		}
		else if (pos >= 0 && pos <= length)
		{
			newPos = pos;
		}
		else
		{
			printf("Error: invalid seek position");
			return -1;
		}

		FilePtr[id]->Seek(newPos);

		return newPos;
	}

	int GetID(char *name)
	{
		return OpenForReadWrite(name, FALSE);
	}

	int GetOpenID(char *name)
	{
		int i = 2;
		while (i < TABLE_SIZE)
		{
			if (FilePtr[i] != NULL && FilePtr[i]->type != IS_SOCKET && strcmp(FilePtr[i]->filename, name) == 0)
			{
				return i;
			}
			i++;
		}
		return -1;
	}

	bool RemoveFile(char *name)
	{
		return Unlink(name) == 0;
	}

	int RemoveSocket(int id)
	{
		if (id < 2 || id >= TABLE_SIZE)
			return -1;
		if (FilePtr[id])
		{
			delete FilePtr[id];
			FilePtr[id] = NULL;
			cerr << "\nSocket closed successfully\n";
			return 0;
		}
		cerr << "\nSocket close failed\n";
		return -1;
	}
};

#else // FILESYS
class FileSystem
{

public:
	OpenFile **FilePtr;

	FileSystem(bool format); // Initialize the file system.
							 // Must be called *after* "synchDisk"
							 // has been initialized.
							 // If "format", there is nothing on
							 // the disk, so initialize the directory
							 // and the bitmap of free blocks.

	bool Create(char *name, int initialSize);
	OpenFile *Open(char *name);
	OpenFile *Open(char *name, int t);
	// Create a file (UNIX creat)

	int AppendFile(char *name); // Open a file (UNIX open)
	int AppendFile(char *name, int t);
	int AppendSocket();
	int Seek(int pos, int id);

	int BlankSpace();

	bool CheckOpenFile(int fileId)
	{
		if (fileId < 0 || fileId >= TABLE_SIZE)
			return false;
		if (FilePtr[fileId] == NULL)
			return false;
		return true;
	}

	bool RemoveFile(char *name); // Delete a file (UNIX unlink)

	void List(); // List all the files in the file system

	void Print(); // List all the files and their contents
	int GetID(char *name);
	int GetOpenID(char *name);
	int RemoveSocket(int id);

private:
	OpenFile *freeMapFile;	 // Bit map of free disk blocks,
							 // represented as a file
	OpenFile *directoryFile; // "Root" directory -- list of
							 // file names, represented as a file
};

#endif // FILESYS

#endif // FS_H
