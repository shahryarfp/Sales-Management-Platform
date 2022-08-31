#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_cmd.h"
#include "mallcheck.h"
char* get_cmd()
{
	char *str = (char*)malloc(sizeof(char));//allocate memory
	int ch, i = 0;//ch is for geting characters
	//loop for get strings
	while ((ch = getchar()) != EOF && ch != '\n')//get char untill '\n'
	{
		str = (char*)realloc(str, sizeof(char)*(i + 1));//reallocate memory to increase its size
		mallcheck(str);//check malloc errors
		str[i] = ch;//put reading chars together
		i++;
	}
	str = (char*)realloc(str, sizeof(char)*(i + 1));//reallocate memory to increase its size
	str[i] = NULL;//put NULL at the end of command line we read
	return str;//return the answer
}