#include "syscall.h"

int
main()
{
    /*
    SpaceId newProc;
    OpenFileId input = CONSOLE_INPUT;
    OpenFileId output = CONSOLE_OUTPUT;
    char prompt[2], ch, buffer[60];
    int i;

    prompt[0] = '-';
    prompt[1] = '-';

    while( 1 )
    {
	Write(prompt, 2, output);

	i = 0;
	
	do {
	
	    Read(&buffer[i], 1, input); 

	} while( buffer[i++] != '\n' );

	buffer[--i] = '\0';

	if( i > 0 ) {
		newProc = Exec(buffer);
		Join(newProc);
	}
    }*/
    SpaceId newProc1;
    SpaceId newProc2;

    newProc2 = Exec("cat");
    newProc1 = Exec("copy");

    Join(newProc2);
	Join(newProc1);

}

