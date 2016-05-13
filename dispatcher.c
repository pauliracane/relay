#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> //Flock
#include <fcntl.h>

#define MAX_SZ 256

int main(void)
{	
	//Initialize character array to take in user input that will later
	//be passed to listener
	char str[MAX_SZ] = {'\0'};
	
	//Create file w/ 777 permissions
	int filedesc = open("/tmp/testfile.txt", O_WRONLY | O_CREAT | O_TRUNC,
						S_IRWXU | S_IRWXG | S_IRWXO);
	//If file failed to be made, tell them it's broken, exit
	if(filedesc < 0)
	{
		    printf("Broken.\n");
			    return 1;
	}
	//Actually give listeners somethign to latch on to
	write(filedesc, "", 22);
	close(filedesc);
	
	while (1)
	{
		//Wait for input; if input is Nothin, or input is Ctrl + D, break
		if ( (fgets(str, MAX_SZ-1 , stdin) ) == NULL || str[0]==0x04)
		{
			break;
		}
		//Reopen file descriptor
		int filedesc = open("/tmp/testfile.txt", O_WRONLY | O_CREAT | O_TRUNC);
		//If file descriptor is null; it failed
		if(filedesc < 0)
		{
			printf("Broken.\n");
			return 1;
		}
		//Set lock on file
		flock(filedesc, LOCK_EX);
		//Overwrite file; if you don't print entire message, break
		if(write(filedesc,str, strlen(str)) != (int) strlen(str))
		{
			write(filedesc,"There was an error writing to testfile.txt\n", 36);
			// strictly not an error, it is allowable for fewer 
			// characters than requested to be written.
			return 1;
		}
		//Unlock file
		flock(filedesc, LOCK_UN);
		//Close file descriptor
		close(filedesc);
	}
	//Remove file
	remove("/tmp/testfile.txt");
	return 0;
}

