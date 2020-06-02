#include<stdio.h>
int main()
{
	unsigned int x = 0x12345678;
	char *ptr;
	
	ptr = (char *)&x;
	printf("%x\n", *ptr);
	printf("%x\n", *(ptr + 1));
	printf("%x\n", *(ptr + 2));
	printf("%x\n", *(ptr + 3));
	return 0;
}
