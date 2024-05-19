#include <stdio.h>
#include <Windows.h>
#include <string.h>

int main()
{
    HANDLE input;
    HANDLE output;
    HANDLE file;
    DWORD lenght;

    // строка с уведомлением на ввод
    char notify[] = "Input text:";

    // строка для хранения вводимых значений, т.е. буфер
    char buffer[255];

    // получения хэндла консольного ввода
    input = GetStdHandle(STD_INPUT_HANDLE);

    // получение хэндла консольного вывода
    output = GetStdHandle(STD_OUTPUT_HANDLE);

    // открытие файла и получение хэндла файла
    file = CreateFile("file.txt",GENERIC_WRITE,NULL,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

    // вывод хэндлов ввода и вывода
    printf("Input handle - %d, output handle - %d\n\n", input, output);
    // writefile( хэндл вывода, строка для вывода,
    // количество символов выводимых, вернувшееся значения выведенных значений,...)
    // предведомление на ввод данных
    WriteFile(output,notify,strlen(notify),NULL,NULL);

    // readfile( хэндл ввода, строка для записи вводимых символов,
    // размер ввода, куда запишется вернувшиеся количество записанных символов,...)
    // ввод пользователя в буфер
    ReadFile(input, buffer, 255, &lenght, NULL);

    // ввод кода позволяющего перейти на следующую строку в выводе
    WriteFile(output,"\n",2,NULL,NULL);

    // вывод введенных символов в буфере. Lenght получил верный размер введенных символов
    WriteFile(output,buffer,lenght, NULL, NULL);
    return 0;
}
