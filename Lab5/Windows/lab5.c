#include <windows.h>
#include <stdio.h>
#include <wincon.h>

int main(){
    int i;
    int x;
    int y;

	HANDLE file_handle;
    HANDLE input_handle;
    HANDLE output_handle;
    HANDLE hW;
    HANDLE hR;
	DWORD bw = 0, length, rc, cbRead;
	INPUT_RECORD infbuf;
	COORD pos1, pos2, text_coord, info_coord, writePos;
	char filename[]="lab5.txt", buf[255], buffer[255], temp[255];
	char ch, is_new_char;
	short attr = BACKGROUND_GREEN;
	output_handle = GetStdHandle( STD_OUTPUT_HANDLE );
	input_handle  = GetStdHandle( STD_INPUT_HANDLE );

   	if(input_handle == INVALID_HANDLE_VALUE || output_handle==INVALID_HANDLE_VALUE){
        return 1;
    }

	file_handle = CreateFile( filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );

    if(file_handle==INVALID_HANDLE_VALUE){
        sprintf(temp,"File not found\n");
        WriteFile(output_handle,temp,strlen(temp),NULL,NULL);
        return 1;
    }

	do {
		rc = ReadFile(file_handle, buffer, 255, &cbRead, NULL);
		WriteFile(output_handle, buffer, cbRead, &cbRead, NULL);
	} while (cbRead != 0);


    SetConsoleMode(input_handle, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    infbuf.EventType = MOUSE_EVENT;

	while(1) {

  		if(ReadConsoleInput(input_handle, &infbuf, 1, &bw)) {

			if(infbuf.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) return 0;

            info_coord.Y = 15;
			info_coord.X = 1;
     		text_coord.Y = 17;
			text_coord.X = 1;

			if(infbuf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {

                    pos1.X = infbuf.Event.MouseEvent.dwMousePosition.X;
       				pos1.Y = infbuf.Event.MouseEvent.dwMousePosition.Y;
					writePos.X = infbuf.Event.MouseEvent.dwMousePosition.X;
					writePos.Y = infbuf.Event.MouseEvent.dwMousePosition.Y;

       				ReadConsoleOutputCharacter(output_handle, &ch, 1, pos1, &bw);
					ReadConsoleOutputCharacter(output_handle, &is_new_char, 1, pos1, &bw);


				if(ch!=' ') {

                    FillConsoleOutputAttribute(output_handle, 0x00, 80, text_coord, &bw);

					WriteConsoleOutputCharacter(output_handle, buf, strlen(buf), text_coord, &bw);

                    SetConsoleCursorPosition(output_handle, info_coord);

                    sprintf(temp,"                     ");
                    WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
					SetConsoleCursorPosition(output_handle, info_coord);

                    sprintf(temp,"(x = %d; y = %d)", pos1.X, pos2.Y);
                    WriteFile(output_handle,temp,strlen(temp), NULL, NULL);
					pos2=pos1;

                    if(is_new_char <= 'Z' && is_new_char >= 'A'){
						is_new_char += 32;
						SetConsoleCursorPosition(output_handle, writePos);
                        SetConsoleTextAttribute(output_handle,3);
                        sprintf(temp, "%c", is_new_char);
                        WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
					}
					else if(is_new_char <= 'z' && is_new_char >= 'a'){
						is_new_char -= 32;
						SetConsoleCursorPosition(output_handle, writePos);
                        SetConsoleTextAttribute(output_handle, 4);
                        sprintf(temp, "%c", is_new_char);
                        WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
					}
                    SetConsoleTextAttribute(output_handle,15);


					while((ch != ' ')&&(pos1.X > 0)) {

						pos1.X--;

          				ReadConsoleOutputCharacter(output_handle, &ch, 1, pos1, &bw);
					}

					if(ch==' ') pos1.X++;
					do {
						pos2.X++;
        				ReadConsoleOutputCharacter(output_handle, &ch, 1, pos2, &bw);
					} while((ch != ' ')&&(pos2.X < 80));
					if(ch == ' ') pos2.X--;
					bw = pos2.X - pos1.X+1;
       				ReadConsoleOutputCharacter(output_handle, buf, bw, pos1, &bw);
                    WriteConsoleOutputCharacter(output_handle, buf, bw, text_coord, &bw);
       				FillConsoleOutputAttribute(output_handle, attr, bw, text_coord, &bw);
       			}
    		}
  		}
	}
    return 0;
}
