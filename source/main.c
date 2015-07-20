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
	init_pair(2,7,4);
	attron(COLOR_PAIR(2));
	move(yInitialPos,xInitialPos);
	addch(ACS_ULCORNER);
	for(x=1;x<BOARD_X_SIZE;x++) {
		addch(ACS_HLINE);
	}
	addch(ACS_URCORNER);
	for(y=1;y<BOARD_Y_SIZE;y++) {
		// ======== -- Conectores lado esquerdo
		move(yInitialPos+y,xInitialPos-2);
		addch(ACS_HLINE);
		addch(ACS_HLINE);
		move(yInitialPos+y,xInitialPos);
		addch(ACS_VLINE);
		for(x=1;x<BOARD_X_SIZE;x++) {
                	addch(' ');
        	}
		move(yInitialPos+y,xInitialPos+BOARD_X_SIZE);
		addch(ACS_VLINE);
		// ======== -- Conectores do lado direito
		addch(ACS_HLINE);
		addch(ACS_HLINE);
	}
	move(yInitialPos+BOARD_Y_SIZE,xInitialPos);
        addch(ACS_LLCORNER);
        for(x=1;x<BOARD_X_SIZE;x++) {
                addch(ACS_HLINE);
        }
        addch(ACS_LRCORNER);	
	attroff(COLOR_PAIR(2));
	
	attron(COLOR_PAIR(1));
	move(yInitialPos+ 1, xInitialPos+BOARD_X_SIZE + 4); printw("      13 - ");
 	move(yInitialPos+ 2, xInitialPos+BOARD_X_SIZE + 4); printw("      12 - ");
 	move(yInitialPos+ 3, xInitialPos+BOARD_X_SIZE + 4); printw("    ~ 11 - ");
 	move(yInitialPos+ 4, xInitialPos+BOARD_X_SIZE + 4); printw("    ~ 10 - ");
 	move(yInitialPos+ 5, xInitialPos+BOARD_X_SIZE + 4); printw("    ~  9 - ");
 	move(yInitialPos+ 6, xInitialPos+BOARD_X_SIZE + 4); printw("       8 - ");
 	move(yInitialPos+ 7, xInitialPos+BOARD_X_SIZE + 4); printw("       7 - ");
 	move(yInitialPos+ 8, xInitialPos+BOARD_X_SIZE + 4); printw("    ~  6 - ");
 	move(yInitialPos+ 9, xInitialPos+BOARD_X_SIZE + 4); printw("    ~  5 - ");
 	move(yInitialPos+10, xInitialPos+BOARD_X_SIZE + 4); printw("       4 - ");
 	move(yInitialPos+11, xInitialPos+BOARD_X_SIZE + 4); printw("    ~  3 - ");
 	move(yInitialPos+12, xInitialPos+BOARD_X_SIZE + 4); printw("       2 - ");
 	move(yInitialPos+13, xInitialPos+BOARD_X_SIZE + 4); printw("RX <-  1 - ");
	move(yInitialPos+14, xInitialPos+BOARD_X_SIZE + 4); printw("RA <-  0 - ");
	attroff(COLOR_PAIR(1));
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
