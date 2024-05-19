#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int lenght;
    int output_handle;
    char buffer[255];

    if (isatty(1))
    {
        char name[] = "file.txt";
        output_handle = open(name, O_CREAT | O_WRONLY);
        if (isatty(0))
        {
            sprintf(buffer, "Input:");
            write(1, buffer, strlen(buffer));
            lenght = read(0, buffer, 100);
            write(output_handle, buffer, lenght - 1);
        }
        else
        {
            sprintf(buffer, "Readed:");
            write(1, buffer, strlen(buffer));
            lenght = read(0, buffer, 100);
            write(1, buffer, lenght);
            write(output_handle, buffer, lenght);
        }
        close(output_handle);
    }
    else
    {
        if (isatty(0))
        {
            sprintf(buffer, "Input:");
            write(2, buffer, strlen(buffer));
            lenght = read(0, buffer, 100);
            write(1, buffer, lenght - 1);
        }
        else
        {
            sprintf(buffer, "Readed:");
            write(2, buffer, strlen(buffer));
            lenght = read(0, buffer, 100);
            write(2, buffer, lenght);
            write(1, buffer, lenght);
        }
    }
    return 0;
}
