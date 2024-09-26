#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define DX 3

void displayInWindowLinesFromOffset(
                WINDOW *win,
                char **lines,
                int linesCount,
                int offsetX,
                int offsetY);

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct stat sb;
	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}
	
	char *buffer;
	if ((buffer = calloc(sb.st_size, sizeof(char))) == NULL) {
		perror("calloc on creating buffer");
		exit(EXIT_FAILURE);
	}
	
	FILE *f;
	if ((f = fopen(argv[1], "r")) == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);	
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *bufferIdx = buffer;
	int linesCount = 0;
	while ((nread = getline(&line, &len, f)) != EOF) {
		line[nread - 1] = '\0';
		strncpy(bufferIdx, line, nread);
		bufferIdx += nread;
		++linesCount;
	}

	char **lines = calloc(linesCount + 1, sizeof(char *));
	if (lines == NULL) {
		perror("calloc on creating lines");
		exit(EXIT_FAILURE);
	}
	lines[0] = buffer;
	for (int i = 0, j = 1; &buffer[i] != bufferIdx; ++i) {
		if (buffer[i] == '\0') {
			lines[j] = buffer + i + 1;
			j++;
		}
	}

	if (line) free(line);
	fclose(f);
	
	WINDOW *win;
	int c = 0;
	initscr();
	noecho();
	cbreak();
	refresh();

	//win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
	win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
	keypad(win, TRUE);
	scrollok(win, TRUE);

        //box(win, 0, 0); 
        //wmove(win, 1, 0); 
	
	mvprintw(0, 0, "%s", argv[1]);
	refresh();
	bool running = true;
	int offsetX = 0, offsetY = 0;
        while(running) {
                box(win, 0, 0); 
                wrefresh(win);
		werase(win);
		displayInWindowLinesFromOffset(win, lines, linesCount, offsetX, offsetY);


		switch(c = wgetch(win)) {
			case 27: running = false; break;
			case KEY_UP: offsetY = offsetY > 0 ? offsetY - 1 : offsetY; break;
			case KEY_DOWN: offsetY = offsetY + 1; break;
			case KEY_RIGHT: offsetX = offsetX + 1; break;
			case KEY_LEFT: offsetX = offsetX > 0 ? offsetX - 1 : offsetX; break;
			default:
				       running = true;

		}
        }

	delwin(win);
	endwin();
	free(buffer);
	free(lines);
	return 0;
}


void displayInWindowLinesFromOffset(
		WINDOW *win,
		char **lines,
		int linesCount,
		int offsetX,
		int offsetY) {
	for (int i = 0; i < win->_maxy && i + offsetY < linesCount; ++i) {
		int length = strlen(lines[i + offsetY]);
		char *lineStart = length > offsetX ? lines[i + offsetY] + offsetX : "";
		mvwaddnstr(win, i, 0, lineStart, win->_maxx);
	}
}














