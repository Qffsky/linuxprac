#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

static void finish(int sig);


int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct stat sb;
	if (stat(argv[1], &sb) == -1) {
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	
	char *buffer;
	if ((buffer = calloc(sb.st_size, sizeof(char))) == NULL) {
		perror("calloc");
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
	while ((nread = getline(&line, &len, f)) != EOF) {
		strncpy(bufferIdx, line, nread);
		bufferIdx += nread;
	}
	
	if (line) free(line);
	fclose(f);
	int num = 0;

	/*
	(void) initscr();
	keypad(stdscr, TRUE);
	(void) nonl();
	(void) cbreak();
	(void) echo();

	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_RED,     COLOR_BLACK);
		init_pair(2, COLOR_GREEN,   COLOR_BLACK);
		init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
		init_pair(4, COLOR_BLUE,    COLOR_BLACK);
		init_pair(5, COLOR_CYAN,    COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE,   COLOR_BLACK);
	}

	for (;;) {
		int c = getch();
		attrset(COLOR_PAIR(num % 8));
		num++;
	}

	bool processing = false;
	for (;;processing) {
		int ch = getch();
	}
	*/
	exit(0);
	finish(0);
}

static void finish(int sig)
{
	endwin();
	exit(0);
}
