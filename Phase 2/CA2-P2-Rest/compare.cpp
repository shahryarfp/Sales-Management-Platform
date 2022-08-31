#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compare.h"

int compare(char a[], char b[])//Not changed
{
	int result = 0, i = 0;
	while (a[i] != NULL&&b[i] != NULL)
	{
		if (a[i] < b[i]) //checking the condition
		{
			result = 1;
			break;
		}
		else if (a[i] > b[i])
		{
			result = 2;
			break;
		}
		i++;
	}
	//for these situation (to compare (the) and (then))
	//smaller word comes first
	if (result == 0)
	{
		if (a[i] == NULL&b[i] != NULL)
		{
			result = 1;
		}
		else if (b[i] == NULL&a[i] != NULL)
		{
			result = 2;//returning result
		}
	}
	return result;
}