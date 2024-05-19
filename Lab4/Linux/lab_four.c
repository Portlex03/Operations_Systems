#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define RED "\033[1;31m"
#define GREEN "\033[4;32m"

int main() {
	char name[] = "file";
	char buffer[255];
    int file;
	int lenght;
	struct flock lock={F_WRLCK, SEEK_SET, 0, 0};
	file = open(name, O_RDWR, 0600);
	while (fcntl(file, F_SETLK, &lock) == -1){
			sprintf(buffer,"\033[15;40H%sError",RED);
			write(1, buffer, strlen(buffer));
			sleep(1+(rand()%3));
	}
    sprintf(buffer,"\033[15;40H%sReaded from file:\033[16;40H",GREEN);
    write(1,buffer,strlen(buffer));
	lenght = read(file, buffer, 80);
    write(1, buffer, lenght);
	sleep(7);
	close(file);
	return 0;
}
