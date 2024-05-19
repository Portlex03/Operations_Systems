#include <windows.h>
#include <stdio.h>

void main() {
    char buf[100];
	char fileName[]="FileOutput.txt";

	DWORD actlen;
	HANDLE hstdin, fileHandle;

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hstdin == INVALID_HANDLE_VALUE) return;

	fileHandle = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                            0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (fileHandle == INVALID_HANDLE_VALUE) return;

    printf("Enter text:\n");
    fflush(stdout);

	if (!ReadFile(hstdin, buf, 90, &actlen, NULL)) return;

	WriteFile(fileHandle, buf, actlen, &actlen, NULL);


	CloseHandle(fileHandle);

}
