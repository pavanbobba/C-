#include<stdio.h>
int minimumSwaps(int arr_count, int* arr) 
{
	int cnt = 0, i, tmp;

	for(i = 0; i < arr_count; i++)
	{
		while((arr[i] - i) > 1)
		{
			tmp = arr[i];
			arr[i] = arr[tmp - 1];
			arr[tmp - 1] = tmp;
			cnt++;
		}
	}
	
	return cnt;
}

int main()
{
	int arr[7] = {7, 1, 3, 2, 4, 5, 6};
	
	printf("minimum swaps required:%d\n", minimumSwaps((sizeof(arr)/4), arr));
	return 0;
}
