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
	char str[MAX_SZ] = {'\0'};

	int filedesc = open("/tmp/testfile.txt", O_WRONLY | O_CREAT | O_TRUNC,
						S_IRWXU | S_IRWXG | S_IRWXO);
	if(filedesc < 0)
	{
		    printf("Broken.\n");
			    return 1;
	}
	write(filedesc, "", 22);
	close(filedesc);
	
	while (1)
	{
		if ( (fgets(str, MAX_SZ-1 , stdin) ) == NULL || str[0]==0x04)
		{
			break;
		}
		int filedesc = open("/tmp/testfile.txt", O_WRONLY | O_CREAT | O_TRUNC);
		if(filedesc < 0)
		{
			printf("Broken.\n");
			return 1;
		}
		flock(filedesc, LOCK_EX);
		if(write(filedesc,str, strlen(str)) != (int) strlen(str))
		{
			write(filedesc,"There was an error writing to testfile.txt\n", 36);
			// strictly not an error, it is allowable for fewer 
			// characters than requested to be written.
			return 1;
		}

		flock(filedesc, LOCK_UN);
		close(filedesc);
	}
	remove("/tmp/testfile.txt");
	return 0;
}

