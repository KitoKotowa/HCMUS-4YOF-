// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
#include "synchconsole.h"

#define MaxFileLength 32
#define MaxNameLength 256
#define MaxBufferLength 1024
#define MAX_FILE_OPEN 20
#define READWRITE 0
#define READONLY 1
#define STD_IN 2
#define STD_OUT 3
#define IS_SOCKET 4
#define IS_FILE 5

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

char *User2System(int virtAddr, int limit)
{
	int i;
	int oneChar;
	char *kernelBuf = NULL;
	kernelBuf = new char[limit + 1];
	if (kernelBuf == NULL)
		return kernelBuf;

	memset(kernelBuf, 0, limit + 1);

	for (i = 0; i < limit; i++)
	{
		kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
		if (oneChar == 0)
		{
			break;
		}
		kernelBuf[i] = (char)oneChar;
	}
	return kernelBuf;
}

int System2User(int virtAddr, int len, char *buffer)
{
	if (len < 0)
		return -1;
	if (len == 0)
		return len;
	int i = 0;
	int oneChar = 0;
	do
	{
		oneChar = (int)buffer[i];
		kernel->machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}

void handle_SC_PrintInt(int number)
{
	int divisor = 1, remainder, quotient;

	// Handle negative numbers
	if (number < 0)
	{
		kernel->synchConsoleOut->PutChar('-');
		number = -number;
	}

	// Find the divisor to get the most significant digit
	while (number / divisor >= 10)
	{
		divisor *= 10;
	}

	// Output each digit one by one
	while (divisor > 0)
	{
		quotient = number / divisor;
		remainder = number % divisor;
		kernel->synchConsoleOut->PutChar(quotient + '0');
		number = remainder;
		divisor /= 10;
	}
}

void IncreasePC()
{
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

void handle_SC_SocketTCP()
{
	kernel->machine->WriteRegister(2, SysSocketTCP());
}

void handle_SC_Connect()
{
	char *ip;
	int socketID, virtAdr, port;
	socketID = kernel->machine->ReadRegister(4);
	virtAdr = kernel->machine->ReadRegister(5);
	port = kernel->machine->ReadRegister(6);
	ip = User2System(virtAdr, MaxBufferLength - 1);
	kernel->machine->WriteRegister(2, SysConnect(socketID, ip, port));
	delete[] ip;
}

void handle_SC_Send()
{
	char *buffer;
	int connection, socketID, virtAdr, len;
	connection = kernel->machine->ReadRegister(2);
	socketID = kernel->machine->ReadRegister(4);
	virtAdr = kernel->machine->ReadRegister(5);
	len = kernel->machine->ReadRegister(6);
	buffer = User2System(virtAdr, MaxBufferLength + 1);
	kernel->machine->WriteRegister(2, SysSend(socketID, buffer, len, connection));
	delete[] buffer;
}

void handle_SC_Receive()
{
	char *buffer;
	int connection, socketID, virtAdr, len;
	connection = kernel->machine->ReadRegister(2);
	socketID = kernel->machine->ReadRegister(4);
	virtAdr = kernel->machine->ReadRegister(5);
	len = kernel->machine->ReadRegister(6);
	buffer = User2System(virtAdr, MaxBufferLength + 1);
	kernel->machine->WriteRegister(2, SysReceive(socketID, buffer, len, connection));
	delete[] buffer;
}

void handle_SC_CloseSocket()
{
	int socketID;
	socketID = kernel->machine->ReadRegister(4);
	kernel->machine->WriteRegister(2, SysCloseSocket(socketID));
}

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	case SyscallException:
		switch (type)
		{
		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");
			printf("\n");
			SysHalt();

			// ASSERTNOTREACHED();
			break;

		case SC_Add:
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			int result;
			result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
							/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << result << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)result);

			break;

		case SC_Create:
		{
			// Input: Dia chi tu vung nho user cua ten file
			// Output: -1 = Loi, 0 = Thanh cong
			// Chuc nang: Tao ra file voi tham so la ten file
			int virtAddr;
			char *filename;
			DEBUG(dbgSys, "\nSC_CreateFile call ...");
			DEBUG(dbgSys, "\nReading virtual address of filename");

			virtAddr = kernel->machine->ReadRegister(4);
			DEBUG(dbgSys, "\nReading filename.");

			filename = User2System(virtAddr, MaxFileLength + 1);
			if (sizeof(filename) == 0)
			{
				printf("\nFile name is not valid");
				kernel->machine->WriteRegister(2, -1); // Return -1 to reg R2
				delete[] filename;
				break;
			}

			if (filename == NULL)
			{
				printf("\nNot enough memory in system");
				kernel->machine->WriteRegister(2, -1);
				delete[] filename;
				break;
			}
			DEBUG(dbgSys, "\nFinish reading filename.");

			if (!kernel->fileSystem->Create(filename, 0))
			{
				printf("\nError create file '%s'", filename);
				kernel->machine->WriteRegister(2, -1);
				delete[] filename;
				break;
			}

			// Tao file thanh cong
			kernel->machine->WriteRegister(2, 0);
			DEBUG(dbgSys, "\nSuccessfully create file " << filename << "\n");

			delete[] filename;
			break;
		}

		case SC_Open:
		{
			// OpenFileID Open(char *name, int type)
			// Input: arg1: name, arg2: type
			// Output: return OpenFileID if success, else -1
			DEBUG(dbgSys, "\nSC_Open call ...");
			DEBUG(dbgSys, "\nReading virtual address of filename");
			int virtAddr = kernel->machine->ReadRegister(4);
			int type = kernel->machine->ReadRegister(5);
			char *filename;
			int block;

			DEBUG(dbgSys, "\nReading filename.");

			filename = User2System(virtAddr, MaxFileLength);

			if (type == READWRITE || type == READONLY) // allow read and readwrite
			{
				block = kernel->fileSystem->AppendFile(filename, type);
				kernel->machine->WriteRegister(2, block);
			}
			else if (type == STD_IN) // stdin
			{
				printf("\nOpen file stdin\n");
				kernel->machine->WriteRegister(2, 0); // OpenID = 0 for std_in
			}
			else if (type == STD_OUT) // stdout
			{
				printf("\nOpen file stdout\n");
				kernel->machine->WriteRegister(2, 1); // OpenID = 1 for std_out
			}
			// for (int i = 0; i < MAX_FILE_OPEN; i++)
			// {
			// 	printf("%d ", kernel->fileSystem->FilePtr[i] == NULL);
			// }

			delete[] filename;
			break;
		}

		case SC_Close:
		{
			// Input id cua file(OpenFileID)
			//  Output: 0: success, -1 fail
			// for (int i = 0; i < MAX_FILE_OPEN; i++)
			// {
			// 	printf("%d ", kernel->fileSystem->FilePtr[i] == NULL);
			// }
			DEBUG(dbgSys, "Open SC_Close");
			int FileID = kernel->machine->ReadRegister(4); // Read ID from reg 4
			DEBUG(dbgSys, "Read file id " << FileID);
			if (FileID >= 0 && FileID < MAX_FILE_OPEN)
			{
				if (kernel->fileSystem->FilePtr[FileID]->type == IS_SOCKET)
				{
					printf("Error: Cannot close socket.\n");
				}
				else if (kernel->fileSystem->FilePtr[FileID] != NULL) // if success
				{
					// delete kernel->fileSystem->FilePtr[FileID]->file;
					// delete kernel->fileSystem->FilePtr[FileID];
					//  DEBUG(dbgSys, "Successfully delete file id: " << FileID);
					kernel->fileSystem->FilePtr[FileID] = NULL;
					kernel->machine->WriteRegister(2, 0);
					DEBUG(dbgSys, "Successfully close file id: " << FileID);
					break;
				}
				else
				{
					printf("\nCannot close file not exist\n");
				}
			}
			else
			{
				printf("\nError: Close file out of %d file descriptors table\n", MAX_FILE_OPEN);
			}
			kernel->machine->WriteRegister(2, -1);
			break;
		}

		case SC_Remove:
		{
			DEBUG(dbgSys, "\nSC_Remove call ...");
			DEBUG(dbgSys, "\nReading virtual address of filename");
			int virtAddr = kernel->machine->ReadRegister(4);
			char *filename;
			int ID, OpenID;
			filename = User2System(virtAddr, MaxNameLength);

			ID = kernel->fileSystem->GetID(filename);
			OpenID = kernel->fileSystem->GetOpenID(filename);

			DEBUG(dbgSys, "\nID: " << ID << "\n");
			DEBUG(dbgSys, "\nOpenID: " << ID << "\n");
			// for (int i = 0; i < MAX_FILE_OPEN; i++)
			// {
			// 	printf("%d ", kernel->fileSystem->FilePtr[i] == NULL);
			// }
			// printf("Is null: %d\n", kernel->fileSystem->FilePtr[ID] == NULL);

			if (ID == -1)
			{
				printf("\nError: Cannot remove non-existent file '%s'\n", filename);
				kernel->machine->WriteRegister(2, -1);
			}
			else if (kernel->fileSystem->CheckOpenFile(OpenID))
			{
				printf("\nError: Cannot remove open file '%s'\n", filename);
				kernel->machine->WriteRegister(2, -1);
			}
			else
			{
				if (kernel->fileSystem->RemoveFile(filename))
				{
					DEBUG(dbgSys, "\nFile " << filename << "removed successfully\n");
					kernel->machine->WriteRegister(2, 0);
				}
				else
				{
					printf("\nError: Cannot remove file '%s'\n", filename);
					kernel->machine->WriteRegister(2, -1);
				}
			}

			delete[] filename;
			break;
		}

		case SC_Read:
		{
			DEBUG(dbgSys, "Open SC_Read call...");
			int virtAddr = kernel->machine->ReadRegister(4);
			int charcount = kernel->machine->ReadRegister(5);
			char *buffer = new char[charcount];
			int fileId = kernel->machine->ReadRegister(6);
			int bytesRead = -1;

			if (kernel->fileSystem->FilePtr[fileId] == NULL)
			{
				printf("Error: Invalid OpenFileID\n");
				kernel->machine->WriteRegister(2, -1);
				delete[] buffer;
				break;
			}

			memset(buffer, 0, charcount); // fill the buffer with zeroes

			if (fileId == 0) // Console In
			{
				int i = 0;
				while (i < charcount)
				{
					buffer[i] = kernel->synchConsoleIn->GetChar();
					if (buffer[i] == EOF || buffer[i] == '\n')
					{
						buffer[i] = '\0';
						bytesRead = i;
						break;
					}
					i++;
				}
				System2User(virtAddr, bytesRead, buffer);
			}
			else if (fileId == 1) // Console Out
			{
				printf("Error: Cannot read from ConsoleOutput\n");
				kernel->machine->WriteRegister(2, -1);
				delete[] buffer;
				break;
			}
			else
			{
				bytesRead = kernel->fileSystem->FilePtr[fileId]->Read(buffer, charcount - 1);
				System2User(virtAddr, bytesRead, buffer);
			}

			DEBUG(dbgSys, "Read " << bytesRead << " chars from file " << fileId << "\n");

			kernel->machine->WriteRegister(2, bytesRead);
			delete[] buffer;

			break;
		}

		case SC_Write:
		{
			int virtAddr = kernel->machine->ReadRegister(4);
			int charcount = kernel->machine->ReadRegister(5);
			int fileId = kernel->machine->ReadRegister(6);
			int bytesWritten = -1;
			int i;
			char *buffer;

			if (kernel->fileSystem->FilePtr[fileId] == NULL)
			{
				printf("Error: Invalid OpenFileID\n");
				kernel->machine->WriteRegister(2, -1);
				delete[] buffer;
				break;
			}

			buffer = User2System(virtAddr, charcount);

			if (fileId == 0) // Console In
			{
				printf("Error: Cannot write to ConsoleInput\n");
				kernel->machine->WriteRegister(2, -1);
				delete[] buffer;

				break;
			}
			else if (fileId == 1) // Console Out
			{
				for (i = 0; i < charcount; i++)
				{
					kernel->synchConsoleOut->PutChar(buffer[i]);
				}
				bytesWritten = charcount;
			}
			else
			{
				if (kernel->fileSystem->FilePtr[fileId]->type == READONLY) // cannot write readonly file
				{
					printf("Error: Cannot write readonly file\n");
					kernel->machine->WriteRegister(2, -1);
					delete[] buffer;

					break;
				}
				else
				{
					DEBUG(dbgSys, "\nAt write file of system\n");
					bytesWritten = kernel->fileSystem->FilePtr[fileId]->Write(buffer, strlen(buffer));
				}
			}

			DEBUG(dbgSys, "Write " << bytesWritten << " chars to file " << fileId << "\n");

			kernel->machine->WriteRegister(2, bytesWritten);
			delete[] buffer;

			break;
		}

		case SC_PrintString:
		{
			DEBUG(dbgSys, "In SC_PrintString\n");
			int virtAddr = kernel->machine->ReadRegister(4);
			int i;
			char *buffer;
			buffer = User2System(virtAddr, MaxBufferLength);
			for (i = 0; i < strlen(buffer); i++)
			{
				kernel->synchConsoleOut->PutChar(buffer[i]);
			}
			DEBUG(dbgSys, "Successfully print string\n");
			delete[] buffer;
			break;
		}

		case SC_PrintInt:
		{
			int value = kernel->machine->ReadRegister(4);
			DEBUG('a', "Printing integer.\n");
			handle_SC_PrintInt(value);
			break;
		}

		case SC_Seek:
		{
			int pos = kernel->machine->ReadRegister(4);
			int fileId = kernel->machine->ReadRegister(5);

			int newPos = kernel->fileSystem->Seek(pos, fileId);

			if (newPos == -1)
			{
				printf("Error: Seek failed\n");
				kernel->machine->WriteRegister(2, -1);
				break;
			}

			kernel->machine->WriteRegister(2, newPos);
			break;
		}

		case SC_SocketTCP:
		{
			handle_SC_SocketTCP();
			break;
		}

		case SC_Connect:
		{
			handle_SC_Connect();
			break;
		}

		case SC_Send:
		{
			handle_SC_Send();
			break;
		}

		case SC_Receive:
		{
			handle_SC_Receive();
			break;
		}

		case SC_CloseSocket:
		{
			handle_SC_CloseSocket();
			break;
		}

		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		IncreasePC();
		return;

	// Nhung exception khac thi in ra mot thong bao loi
	case PageFaultException:
		DEBUG(dbgSys, "No valid translation found\n");
		printf("No valid translation found\n");
		SysHalt();
		break;

	case ReadOnlyException:
		DEBUG(dbgSys, "Write attempted to page marked \"read-only\"\n");
		printf("Write attempted to page marked \"read-only\"\n");
		SysHalt();
		break;

	case BusErrorException:
		DEBUG(dbgSys, "Translation resulted in an invalid physical address\n");
		printf("Translation resulted in an invalid physical address\n");
		SysHalt();
		break;

	case AddressErrorException:
		DEBUG(dbgSys, "Unaligned reference or one that was beyond the end of the address space\n");
		printf("Unaligned reference or one that was beyond the end of the address space\n");
		SysHalt();
		break;

	case OverflowException:
		DEBUG(dbgSys, "Integer overflow in add or sub\n");
		printf("Integer overflow in add or sub\n");
		SysHalt();
		break;

	case IllegalInstrException:
		DEBUG(dbgSys, "Unimplemented or reserved instr\n");
		printf("Unimplemented or reserved instr\n");
		SysHalt();
		break;

	case NumExceptionTypes:
		DEBUG(dbgSys, "Number exception types\n");
		printf("Number Exception types\n");
		SysHalt();
		break;

	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}
