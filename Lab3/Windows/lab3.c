#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HANDLE output, file_handle;
void gotoxy (int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(output,coordinates);
}

int main(){
    output=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD lenght;
	int error = 0;
    char temp[255];
    RECT rect = {0};
    GetWindowRect(GetConsoleWindow(), &rect);
    int y = (rect.bottom - rect.top)/50;
    int x = (rect.right - rect.left)/20;

    do
    {
        system("cls");

        file_handle = CreateFile("file.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        gotoxy(x,y);
        sprintf(temp,"file handle = %d",file_handle);
        SetConsoleTextAttribute(output,10);
        WriteFile(output,temp,strlen(temp),NULL,NULL);
        if(file_handle == INVALID_HANDLE_VALUE){
            error = GetLastError();
            gotoxy(x,y+2);
            sprintf(temp,"error = %d",error);
            SetConsoleTextAttribute(output,4);
            WriteFile(output,temp,strlen(temp),NULL,NULL);
            if(error == 2){
                gotoxy(x,y+4);
                SetConsoleTextAttribute(output,4);
                sprintf(temp,"File not found");
                WriteFile(output,temp,strlen(temp),NULL,NULL);
                Sleep(7000);
                return 0;
            }
            if(error == 32){
                gotoxy(x,y+4);
                SetConsoleTextAttribute(output,4);
                sprintf(temp,"File is used");
                WriteFile(output,temp,strlen(temp),NULL,NULL);
            }

        }else{
            break;
        }
        Sleep(100);
    }while(1);

    SetConsoleTextAttribute(output,14);
    sprintf(temp,"File open!");
    WriteFile(output,temp,strlen(temp),NULL,NULL);
	ReadFile(file_handle,temp,100,&lenght,NULL);
    gotoxy(x,y+6);
    SetConsoleTextAttribute(output,15);
    WriteFile(output,temp,lenght,&lenght,NULL);
	Sleep(7000);
	CloseHandle(file_handle);
    return 0;
}
