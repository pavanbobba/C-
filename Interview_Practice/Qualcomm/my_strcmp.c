//strcmp implementation
#include<stdio.h>
#include <string.h>

#define STR_SIZE 50

int my_str_length(char *p)
{
	int ret = 0, loop_var = 0;
	if(p)
	{
		while(p[loop_var] != '\0')
			loop_var++;
	}
	return loop_var;
}

int my_cmp(char * p1, char * p2)
{
	int l1, l2, loop_var = 0;

	if(p1 && p2)
	{
		l1 = my_str_length(p1);
		l2 = my_str_length(p2);

		if(l1 == l2)
		{
			while(loop_var < l1)
			{
				if(p1[loop_var] != p2[loop_var])
					break;
				loop_var++;
			}
			loop_var = p1[loop_var] - p2[loop_var];
		}
		else
		{
			loop_var = l1 - l2;
		}
	}
	else
	{
		loop_var = -1;
	}
	
	
	return loop_var;
}

int main()
{
//	int loop_var = 0;
	char str1[STR_SIZE], str2[STR_SIZE];
	// while(loop_var < STR_SIZE)
	// {
	// 	str1[loop_var] = '\0';
	// 	str2[loop_var] = '\0';

	// 	loop_var++;
	// }
	printf("enter the strings\n");
	printf("str1:\n");
	fgets(str1, sizeof(str1), stdin);
	printf("str2:\n");
	fgets(str2, sizeof(str2), stdin);
	printf("%d\n", my_cmp(str1, str2));

	//for cross checking purpose
	printf("strcmp returned %d\n", strcmp(str1, str2));
	return 0;
}
