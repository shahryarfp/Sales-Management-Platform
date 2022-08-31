#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mallcheck.h"
void mallcheck(char* mall)
{
	if (mall == NULL)
	{
		printf("Malloc Error!\n");
		exit(EXIT_FAILURE);
	}
}