#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h> //Flock


#define MAX_SZ 256

int main()
{
	//Declare storage spaces
	char buff[MAX_SZ-1] = {'\0'};
	char input[MAX_SZ-1] = {'\0'};
	while (1)
	{
		//Open file for Read
		int filedesc = open("/tmp/testfile.txt", O_RDONLY);
		//Error check the opening of the file
		if (filedesc < 0)
		{
			//If you've gone through teh loop, you can be sure the 
			//dispatcher closed
			if ( input[0] )
			{
				printf("Dispatcher has closed.\n");
			}
			else
			{
				printf("Can't find file /tmp/testfile.txt\n");
			}
			close(filedesc);
			return 1;
		}
		//Put shared lock on file
		flock(filedesc, LOCK_SH);
		//Wipe Input
		for (int x = 0; x < MAX_SZ-1; x++)
			input[x] = '\0';
		//REad in file
		if(read(filedesc,input,MAX_SZ))
		{
			//Compare to last iteration
			//If it's changed, print new line
			if (strcmp(buff, input))
			{
				strncpy(buff, input, MAX_SZ-1);
				printf("%s", buff);
			}
		}
		//Unlock
		flock(filedesc, LOCK_UN);
		close(filedesc);
	}
	return 0;
}

