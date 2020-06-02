#include<stdio.h>

//long arrayManipulation(int n, int queries_rows, int queries_columns, int** queries)
long arrayManipulation(int n, int queries_rows, int queries_columns, int (* queries)[3])
{
	int arr[n], i, j; long big = 0;

	for(i = 0; i < n; i++)
		arr[i] = 0;

	for(i = 0; i < queries_rows; i++)
	{
		for(j = queries[i][0]; j < queries[i][1]; j++)
		{
			arr[j] += queries[i][2];
			if(arr[j] > big)
				big = arr[j];
		}
	}
	
	return big;	
}

int main()
{
	int n = 10;
	//int arr[3][3] = {1, 5, 3, 4, 8, 7, 6, 9, 1};
	int arr[4][3] = {2, 6, 8, 3, 5, 7, 1, 8, 1, 5, 9, 15};
	
	printf("maximum number: %ld\n", arrayManipulation(n, 4, 3, arr));
	return 0;
}
