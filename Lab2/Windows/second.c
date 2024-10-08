#include <stdio.h>
#include <windows.h>

void main() {
	char buf[100] = "";
	char fileName[]="FileOutput.txt";
    const int len = 7;

	DWORD actlen;
	HANDLE hstdin, hstdout;
    HANDLE fileHandleFirst, fileHandleSecond, fileHandleThird;

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	fileHandleFirst = CreateFile(fileName, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ,
                                 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DuplicateHandle (GetCurrentProcess(), fileHandleFirst, GetCurrentProcess(), &fileHandleSecond, 0, FALSE, DUPLICATE_SAME_ACCESS);

	fileHandleThird = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (fileHandleThird == INVALID_HANDLE_VALUE) return;

	printf("%d\n%d\n%d\n", fileHandleFirst, fileHandleSecond, fileHandleThird);
    fflush(stdout);

	SetFilePointer(fileHandleFirst, 10, 0, FILE_BEGIN);

	if (!ReadFile(fileHandleFirst, buf, 90, &actlen, NULL)) return;
	WriteFile(hstdout, buf, len, &actlen, NULL);
	printf("\n");
    fflush(stdout);

	if (!ReadFile(fileHandleSecond, buf, 90, &actlen, NULL)) return;
	WriteFile(hstdout, buf, len, &actlen, NULL);
	printf("\n");
    fflush(stdout);

	if (!ReadFile(fileHandleThird, buf, 90, &actlen, NULL)) return;
	WriteFile(hstdout, buf, len, &actlen, NULL);
    printf("\n");
    fflush(stdout);

printf("FILE_SHARE_READ=%d\n",FILE_SHARE_READ);
printf("FILE_SHARE_WRITE=%d\n",FILE_SHARE_WRITE);
printf("FILE_SHARE_READ | FILE_SHARE_WRITE=%d\n", FILE_SHARE_READ | FILE_SHARE_WRITE);

printf("FILE_SHARE_READ || FILE_SHARE_WRITE=%d\n", FILE_SHARE_READ || FILE_SHARE_WRITE);

	CloseHandle(fileHandleFirst);
	CloseHandle(fileHandleSecond);
	CloseHandle(fileHandleThird);
	getchar();
}
