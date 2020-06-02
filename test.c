#include<stdio.h>
int main()
{
	struct A{
		int b; 
		int c;
	};
	struct A obj = {
		.b = 10,
		.c = 20,
	};
/*	obj = {
		.b = 10, 
		.c = 20
	};*/
	printf("%d %d\n", obj.b, obj.c);
	int x = 1;
	printf("%d" + 1, x);
	Int a=1;
Printf("%dha"+1,a);
	return 0;
}
