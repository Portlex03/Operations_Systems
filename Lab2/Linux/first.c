#include <stdio.h>
#include <fcntl.h>

int main()
{
	char char_massive[50];
	int kolch;
	int fhandle;

    fhandle=open("datafile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    kolch = sprintf(char_massive,"Enter text:\n");
    write(1, char_massive, kolch);
	kolch=read(0, char_massive, 50);
	write(fhandle, char_massive, kolch);
	close(fhandle);
    return 0;
}
