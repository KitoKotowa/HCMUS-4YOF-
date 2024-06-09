// openfile.h
//	Data structures for opening, closing, reading and writing to
//	individual files.  The operations supported are similar to
//	the UNIX ones -- type 'man open' to the UNIX prompt.
//
//	There are two implementations.  One is a "STUB" that directly
//	turns the file operations into the underlying UNIX operations.
//	(cf. comment in filesys.h).
//
//	The other is the "real" implementation, that turns these
//	operations into read and write disk sector requests.
//	In this baseline implementation of the file system, we don't
//	worry about concurrent accesses to the file system
//	by different threads.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef OPENFILE_H
#define OPENFILE_H

#include "copyright.h"
#include "utility.h"
#include "sysdep.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define READWRITE 0
#define READONLY 1
#define STD_IN 2
#define STD_OUT 3
#define IS_SOCKET 4

#ifdef FILESYS_STUB // Temporarily implement calls to
					// Nachos file system as calls to UNIX!
					// See definitions listed under #else
class OpenFile
{

public:
	int type;
	int file;
	char *filename;

	OpenFile(int f) // open the file
	{
		file = f;
		type = 0;
		seekPosition = 0;
	}

	OpenFile(int sector, int t)
	{
		file = sector;
		type = t;
		seekPosition = 0;
	}

	OpenFile(int sector, char *name)
	{
		file = sector;
		type = 0;
		filename = new char[strlen(name) + 1];
		strcpy(filename, name);
		seekPosition = 0;
	}

	OpenFile(int f, char *name, int t)
	{
		file = f;
		type = t;
		filename = new char[strlen(name) + 1];
		strcpy(filename, name);
		seekPosition = 0;
	}
	~OpenFile()
	{
		Close(file);
	} // close the file

	int ReadAt(char *into, int numBytes, int position)
	{
		Lseek(file, position, 0);
		return ReadPartial(file, into, numBytes);
	}
	int WriteAt(char *from, int numBytes, int position)
	{
		Lseek(file, position, 0);
		WriteFile(file, from, numBytes);
		return numBytes;
	}
	int Read(char *into, int numBytes)
	{
		int numRead = -1;
		if (type == IS_SOCKET)
		{
			memset(into,0,numBytes);
			numRead = read(file, into, numBytes);
			//cerr << "\nSocket file read in openfile.h\n";
		}
		else
		{
			numRead = ReadAt(into, numBytes, seekPosition);
			seekPosition += numRead;
		}
		//cerr << "\nRead file in openfile.h\n";
		return max(numRead, -1);
	}
	int Write(char *from, int numBytes)
	{
		int numWritten = -1;
		if (type == IS_SOCKET)
		{
			numWritten = send(file, from, numBytes, 0);
			//cerr << "\nSocket file written in openfile.h\n";
		}
		else
		{
			numWritten = WriteAt(from, numBytes, seekPosition);
			seekPosition += numWritten;
		}
		//cerr << "\nFile written in openfile.h\n";
		return max(numWritten, -1);
	}

	int Length()
	{
		Lseek(file, 0, 2);
		return Tell(file);
	}
	void Seek(int position)
	{
		seekPosition = position;
	}

	int GetPos()
	{
		return seekPosition;
	}

	int Connect(char *ip, int port)
	{
		if (file == -1)
			return -1;

		struct sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(ip);
		server.sin_port = htons(port);

		if (connect(file, (struct sockaddr *)&server, sizeof(server)) < 0)
			cerr << "\nConnection failed\n";
			return -1;
		cerr << "\nConnected\n";
		return 0;
	}

	int Send(char *buffer, int len)
	{
		if (file == -1)
			return -1;
		int cnt = send(file, buffer, strlen(buffer), 0);
		if (cnt < 0)
			return -1;
		//cerr << "\nSent in openfile.h\n";
		return cnt;
	}

	int Receive(char *buffer, int len)
	{
		if (file == -1)
			return -1;
		int cnt = read(file, buffer, len);
		if (cnt < 0)
			return -1;
		//cerr << "\nReceived in openfile.h\n";
		return cnt;
	}

private:
	int seekPosition;
};

#else // FILESYS
class FileHeader;

class OpenFile
{

public:
	int file;
	int type;
	char *filename;

	OpenFile(int sector); // Open a file whose header is located
						  // at "sector" on the disk

	OpenFile(int sector, char *name);

	OpenFile(int sector, char *name, int t);

	~OpenFile(); // Close the file

	void Seek(int position); // Set the position from which to
							 // start reading/writing -- UNIX lseek

	int Read(char *into, int numBytes); // Read/write bytes from the file,
										// starting at the implicit position.
										// Return the # actually read/written,
										// and increment position in file.
	int Write(char *from, int numBytes);

	int ReadAt(char *into, int numBytes, int position);
	// Read/write bytes from the file,
	// bypassing the implicit position.
	int WriteAt(char *from, int numBytes, int position);

	int GetPos()
	{
		return seekPosition;
	}

	int Length(); // Return the number of bytes in the
				  // file (this interface is simpler
				  // than the UNIX idiom -- lseek to
				  // end of file, tell, lseek back
	int Connect(char *ip, int port);

	int Send(char *buffer, int len);

	int Receive(char *buffer, int len);

private:
	FileHeader *hdr;  // Header for this file
	int seekPosition; // Current position within the file
};

#endif // FILESYS

#endif // OPENFILE_H
