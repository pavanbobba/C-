#include<stdio.h>

void merge(int *arr, int low, int mid, int high)
{
	int i, j, k, arr1[7];

	for(i = low, j = mid + 1, k = 0; ((i <= mid) && (j <= high)); k++)
	{
		if(arr[i] < arr[j])
			arr1[k] = arr[i++];
		else
			arr1[k] = arr[j++];
	}	
	while(i <= mid)
		arr1[k++] = arr[i++];
	while(j <= high)
		arr1[k++] = arr[j++];
	i = low;
	k = 0;
	while(i <= high)
		arr[i++] = arr1[k++];
}

void do_sort(int *arr, int low, int high)
{
	int mid;

	if(low < high)
	{
		mid = (low + high) / 2;
		do_sort(arr, low, mid);		
		do_sort(arr, mid + 1, high);
		
		merge(arr, low, mid, high);		
	}
}

int main()
{	
	int arr[7] = {5, 1, 4, 19, 11, 6, 2};
	int size, low = 0, i;
	
	size = (sizeof(arr)/sizeof(arr[0]));

	for(i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
	do_sort(arr, low, size - 1);

	for(i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
