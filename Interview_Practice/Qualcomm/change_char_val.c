#include<stdio.h>
int main()
{
	char *c = "Hello World";
	char **ptr;

/*	*ptr = c;
	
	*(*ptr) = 'h';
	*(*(ptr + 6)) = 'w';*/

	printf("%s\n", c);
	return 0;
}
