#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "rangeClass.h"

void argparse(int argc, char *argv[], int *start, int *stop, int *step);
void help();

int
main(int argc, char *argv[])
{
	range I;
	argparse(argc, argv, &I.start,  &I.stop, &I.step);
	for (range_init(&I); range_run(&I); range_next(&I))
		printf("%d\n", range_get(&I));
	return 0;
}


void
argparse(int argc, char *argv[], int *start, int *stop, int *step)
{
	if (argc > 4 || argc < 2) {
		help();
		exit(0);
	}

	switch (argc) {
		case 4:
			*start = strtol(argv[1], NULL, 10);
			*stop  = strtol(argv[2], NULL, 10);
			*step  = strtol(argv[3], NULL, 10); break;
		case 3:
			*start = strtol(argv[1], NULL, 10);
			*stop  = strtol(argv[2], NULL, 10);
			*step  = 1; break;
		case 2:
			*start = 0;
			*stop  = strtol(argv[1], NULL, 10);
			*step  = 1; break;
		default:
	}

}

void
help()
{
	printf("Usage:\n"
		"./range <STOP>\n"
		"./range <START> <STOP>\n"
		"./range <START> <STOP> <STEP>\n"
		"options:\n"
		"\t <START>  int value for first value of range, default value is 0\n"
		"\t <STOP>   int value for upper limit of range\n"
		"\t <STEP>   int value for stepping up, default value is 0\n"
		"Prints range of values, starting from <START>,\nup to but not"
		" including <STOP>, with step <STEP>\n");
}
