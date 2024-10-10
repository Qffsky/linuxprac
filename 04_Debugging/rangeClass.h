#include <stdbool.h>

typedef struct range {
	int start;
	int stop;
	int step;
} range;

void range_init(struct range *R);
bool range_run(struct range *R);
void range_next(struct range *R);
int range_get(struct range *R);
