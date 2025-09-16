#include <ncurses.h>

int main(int argc, char * argv[]){
	initscr();
	move(LINES/2 - 1, COLS/2 - 1);
	addstr("Hello!");
	getch();
	endwin();
	return 0;
}
