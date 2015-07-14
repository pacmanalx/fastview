#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <ncurses.h>

#define BOARD_X_SIZE 40
#define BOARD_Y_SIZE 18

struct winsize terminalSize;

void initScreen(void) {
	initscr();
	noecho();
	nocbreak();
	start_color();
}

void closeScreen(void) {
	endwin();
}

void getScreenSize(void) {
	if (ioctl(0, TIOCGWINSZ, (char *) &terminalSize) < 0) {
		printf("The program cannot determine terminal size.\r\n\r\n");
		exit(1);
	}
}

void clearScreen(int backgroundColor) {
	int x;
	int y;
	init_pair(1,7,backgroundColor);
	attron(COLOR_PAIR(1));
	for(y=0;y<terminalSize.ws_row;y++) {
		for(x=0;x<terminalSize.ws_col;x++) {
			move(y,x);
			printw(" ");
		}
	}
	attroff(COLOR_PAIR(1));
}

void drawBoard(void) {
	int x;
	int y;
	int xInitialPos=(terminalSize.ws_col/2)-(BOARD_X_SIZE/2);
	int yInitialPos=(terminalSize.ws_row/2)-(BOARD_Y_SIZE/2);
	move(yInitialPos,xInitialPos);
	addch(ACS_ULCORNER);
	for(x=1;x<BOARD_X_SIZE;x++) {
		addch(ACS_HLINE);
	}
	addch(ACS_URCORNER);
	for(y=1;y<BOARD_Y_SIZE;y++) {
		move(yInitialPos+y,xInitialPos);
		addch(ACS_VLINE);
		move(yInitialPos+y,xInitialPos+BOARD_X_SIZE);
		addch(ACS_VLINE);
	}
	move(yInitialPos+BOARD_Y_SIZE,xInitialPos);
        addch(ACS_LLCORNER);
        for(x=1;x<BOARD_X_SIZE;x++) {
                addch(ACS_HLINE);
        }
        addch(ACS_LRCORNER);	
}

int main(void) {
	initScreen();
	getScreenSize();
	clearScreen(3);
	drawBoard();
	move(1,1);
	printw("Terminal size is %dx%d", terminalSize.ws_col, terminalSize.ws_row);
	getch();
	closeScreen();
	return(0);
}
