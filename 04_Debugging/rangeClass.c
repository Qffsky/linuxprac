#include "rangeClass.h"

#include <stdbool.h>

void
range_init(struct range *R)
{
	
}

bool
range_run(struct range *R)
{
	return R->start < R->stop;
}

void
range_next(struct range *R)
{
	R->start += R->step;
}

int
range_get(struct range *R)
{
	return R->start;
}
