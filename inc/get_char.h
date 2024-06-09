#ifndef HANGMAN_GETCHAR_HEADER
#define HANGMAN_GETCHAR_HEADER

#include <termio.h>

// 1文字読んで返す
char GetCharactor_get(){
	struct termio prev;
	ioctl(0, TCGETA, &prev);

	struct termio next = prev;
	next.c_lflag &= ~(ICANON);
	ioctl(0, TCSETAW, &next);

	char c = getchar();

	ioctl(0, TCSETAW, &prev);

	return c;
}	

#endif
