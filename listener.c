#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h> //Flock


#define MAX_SZ 256

int main()
{
	char buff[MAX_SZ-1] = {'\0'};
	char input[MAX_SZ-1] = {'\0'};
	for(;;)
	{
		int filedesc = open("testfile.txt", O_RDONLY);
		if (filedesc < 0)
		{
			printf("Error opening testfile.txt.  Check to ensure file exists,"
					" and then try again.\n");
			printf("Note:  Dispatcher removes the file when it finishes.\n");
			close(filedesc);
			return 1;
		}
		flock(filedesc, LOCK_SH);
		for (int x = 0; x < MAX_SZ-1; x++)
			input[x] = '\0';
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

