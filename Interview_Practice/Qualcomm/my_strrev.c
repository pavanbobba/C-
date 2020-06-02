//strrev implementation
#include<stdio.h>

#define STR_SIZE 50

int my_str_length(const char *p)
{
	int ret = 0, loop_var = 0;
	if(p)
	{
		while(p[loop_var] != '\0')
			loop_var++;
	}
	return loop_var;
}

void my_strrev(char * p)
{
	int l, loop_var;
	char tmp;

	if(p)
	{
		l = my_str_length(p);
		l--;
//		printf("length of string: %d\n", l);

		if(l)
		{
			if(!(l%2))
			{
				for(loop_var = 0; loop_var < (l/2); loop_var++)
				{
					tmp = p[l - loop_var];
					p[l - loop_var] = p[loop_var];
					p[loop_var] = tmp;
				}
			}
			else
			{
				for(loop_var = 0; loop_var < ((l + 1)/2); loop_var++)
				{
					tmp = p[l - loop_var];
					p[l - loop_var] = p[loop_var];
					p[loop_var] = tmp;
				}
			}
		}
	
	}
//	printf("in func %s\n", (const char *)p);
}

int main()
{
//	int loop_var = 0;
	char str[STR_SIZE];
	// while(loop_var < STR_SIZE)
	// {
	// 	str1[loop_var] = '\0';
	// 	str2[loop_var] = '\0';

	// 	loop_var++;
	// }
	printf("enter the string\n");
	
	fgets(str, sizeof(str), stdin);
	my_strrev(str);
	printf("%s\n", str);

	return 0;
}
