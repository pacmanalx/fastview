#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <ncurses.h>

struct winsize terminalSize;

void initScreen(void) {
	initscr();
	noecho();
	nocbreak();
}

void closeScreen(void) {
	endwin();
}

void getScreenSize(void) {
	if (ioctl(0, TIOCGWINSZ, (char *) &terminalSize) < 0) {
		printf("The program canno't determine terminal size.\r\n\r\n");
		exit(1);
	}
}

int main(void) {
	initScreen();
	getScreenSize();
	move(10,10);
	printw("Terminal size is %dx%d", terminalSize.ws_col, terminalSize.ws_row);
	getch();
	closeScreen();
	return(0);
}
