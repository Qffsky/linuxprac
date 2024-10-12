#include "rangeClass.h"

#include <stdbool.h>

void
range_init(struct range *R)
{
	R->current = R->start;	
}

bool
range_run(struct range *R)
{
	return R->current < R->stop;
}

void
range_next(struct range *R)
{
	R->current += R->step;
}

int
range_get(struct range *R)
{
	return R->current;
}
