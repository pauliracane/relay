#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h> //Flock


#define MAX_SZ 100

int main()
{
	char buff[MAX_SZ-1] = {'\0'};
	char input[MAX_SZ-1] = {'\0'};
	for(;;)
	{
		int filedesc = open("testfile.txt", O_RDONLY);
		if (filedesc < 0)
		{
			return 1;
		}
		flock(filedesc, LOCK_SH);
		if(read(filedesc,input,MAX_SZ))
		{
			if (strcmp(buff, input))
			{
				strncpy(buff, input, MAX_SZ-1);
				printf("%s", buff);
			}
		}
		flock(filedesc, LOCK_UN);
		close(filedesc);
	}
	return 0;
}

