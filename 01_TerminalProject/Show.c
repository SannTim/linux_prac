#include <ncurses.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define DX 7
#define DY 3

FILE *fil;

long count_lines(FILE *fp, int *max_sym) {
    long lines = 0;
    char c;
	*max_sym = 0;
    fseek(fp, 0, SEEK_SET);
	int curs = 0;
    while (fscanf(fp, "%c", &c) == 1) {
        if (c == '\n'){
			lines++;
			if (curs > *max_sym)
				*max_sym = curs;
			curs = 0;
		}
		curs++;
    }

    fseek(fp, -1, SEEK_END);
    if (fscanf(fp, "%c", &c) == 1 && c != '\n') {
        lines++;
    }

    fseek(fp, 0, SEEK_SET);
    return lines;
}

char **read_lines(FILE *fp, int start, int end, int *lines_out, int width) {
	fseek(fp, 0, SEEK_SET);
    if (start > end || start < 1) {
        *lines_out = 0;
        return NULL;
    }

    int line_no = 1;
    char **result = NULL;
    int count = 0;

    int cap = 0;
    char *buf = NULL;
    int buflen = 0;

    unsigned char c;
    while (fscanf(fp, "%c", &c) == 1) {
        if (buflen + 1 >= cap) {
            cap = cap ? cap * 2 : 128;
            buf = realloc(buf, cap);
        }
        buf[buflen++] = c;

        if (c == '\n' || buflen == width) {
            buf[buflen] = '\0';

            if (line_no >= start && line_no <= end) {
                result = realloc(result, sizeof(char*) * (count + 1));
                result[count] = malloc(buflen + 1);
                for (int i = 0; i <= buflen; i++) result[count][i] = buf[i];
                count++;
            }

            buflen = 0;
            line_no++;
        }

        if (line_no > end) break;
    }


    if (buflen > 0 && line_no >= start && line_no <= end) {
        buf[buflen] = '\0';
        result = realloc(result, sizeof(char*) * (count + 1));
        result[count] = malloc(buflen + 1);
        for (int i = 0; i <= buflen; i++) result[count][i] = buf[i];
        count++;
    }

    free(buf);
	fseek(fp, 0, SEEK_SET);
    *lines_out = count;
    return result;
}



int main(int argc, char *argv[]){
	WINDOW *frame,*win;
	if (argc != 2){
		printf("Need at least 2 arguments bruh\n");
		return -1;
	}
	fil = fopen(argv[1],"r");
	
	int c = 0;
	int max_stolb;
	int max_line = count_lines(fil, &max_stolb); 
	setlocale(LC_ALL, "");
	initscr();
    noecho();
    cbreak();
    refresh();

	frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
	box(frame, 0, 0);
    mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), "Читалочка");
    wrefresh(frame);

	win = newwin(LINES - 2*DY - 2, COLS - 2*DX-2, DY+1, DX+1);
    keypad(win, TRUE);
    scrollok (win, TRUE);
	int line = 1;
	int stolb =  0;
	int out;

	char ** lines = read_lines(fil, line, line + LINES - 2*DY - 4, &out, COLS - 2*DX-2);

	for(int i = 0; i < out; i++) {
		wprintw(win, "%s", lines[i]);
		free(lines[i]);
	}
	free(lines);
    while((c = wgetch(win)) != 27 && (c != 113)) {
		// wprintw(win, "%d line: %d stolb: %d \n", c, line, stolb);
		if (c == 259 && line != 1) line--;
		if (c == 258 && line < max_line) line++;
		if (c == 260 && stolb != 0) stolb--;
		if (c == 261 && stolb  + (COLS - 2*DX - 2) <= max_stolb) stolb++;
		char ** lines = read_lines(fil, line, line + LINES - 2*DY - 4, &out, COLS - 2*DX-2);
		wclear(win);
		for(int i = 0; i < out; i++) {
			wprintw(win, "%s", lines[i]);
			free(lines[i]);
		}
		free(lines);
		// wprintw(win, "%d line: %d stolb: %d \n", c, line, stolb);
	}
    delwin(win);
    delwin(frame);
    endwin();
    return 0;
}
