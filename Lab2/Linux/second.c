#include <stdio.h>
#include <fcntl.h>

void main(){
	int fhandle1,
    fhandle2,
    fhandle3,
    bytes_count;
	char handle_handler[50];

	fhandle1 = open("datafile", O_RDONLY);
	fhandle2 = dup(fhandle1);
	fhandle3 = open("datafile", O_RDONLY);
    bytes_count = sprintf(handle_handler, "%d handle1\n", fhandle1);
    write(1, handle_handler, bytes_count);
    bytes_count = sprintf(handle_handler,"%d handle2\n", fhandle2);
    write(1, handle_handler,bytes_count);
    bytes_count = sprintf(handle_handler,"%d handle3\n", fhandle3);
    write(1, handle_handler, bytes_count);

	lseek(fhandle2, 10, SEEK_SET);
    bytes_count=read(fhandle1, handle_handler, 7);
	write(1, handle_handler, bytes_count);

	bytes_count=read(fhandle2, handle_handler, 7);
	write(1, handle_handler, bytes_count);

	bytes_count=read(fhandle3, handle_handler, 7);
	write(1, handle_handler, bytes_count);

}
