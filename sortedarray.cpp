#include <bits/stdc++.h>
using namespace std;
void selectionSort(int a[], int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])
				min = j;
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}
/* Standard Binary Search function*/
int binarySearch(int arr[], int low,
		int high, int key)
{
	if (high < low)
		return -1;

	int mid = (low + high) / 2; /*low + (high - low)/2;*/
	if (key == arr[mid])
		return mid;

	if (key > arr[mid])
		return binarySearch(arr, (mid + 1), high, key);

	// else
	return binarySearch(arr, low, (mid - 1), key);
}

/* Function to get pivot. For array 3, 4, 5, 6, 1, 2
   it returns 3 (index of 6) */
int findPivot(int arr[], int low, int high)
{
	// base cases
	if (high < low)
		return -1;
	if (high == low)
		return low;

	int mid = (low + high) / 2; /*low + (high - low)/2;*/
	if (mid < high && arr[mid] > arr[mid + 1])
		return mid;

	if (mid > low && arr[mid] < arr[mid - 1])
		return (mid - 1);

	if (arr[low] >= arr[mid])
		return findPivot(arr, low, mid - 1);

	return findPivot(arr, mid + 1, high);
}

/* Searches an element key in a pivoted
   sorted array arr[] of size n */
int pivotedBinarySearch(int arr[], int n, int key)
{
	int pivot = findPivot(arr, 0, n - 1);

	// If we didn't find a pivot,
	// then array is not rotated at all
	if (pivot == -1)
		return binarySearch(arr, 0, n - 1, key);

	// If we found a pivot, then first compare with pivot
	// and then search in two subarrays around pivot
	if (arr[pivot] == key)
		return pivot;

	if (arr[0] <= key)
		return binarySearch(arr, 0, pivot - 1, key);

	return binarySearch(arr, pivot + 1, n - 1, key);
}
int main() {
	int num=1024;
	for(int i=10; i<27; ++i){
		int n;
		int *array = new int[num];
		for(int j=0; j<num ; ++j){
			array[j] = rand();
		}
		clock_t tinsert;
		tinsert = clock();
		selectionSort(array, num);
		tinsert = clock() - tinsert;
		clock_t tsearch;
		tsearch = clock();
		for(int j=0; j<100000; ++j){
			n=rand();
			int x=pivotedBinarySearch(array, num, n);
		}
		tsearch = clock() - tsearch;
		delete []array;
		cout<<"sortedarray,"<<i<<","<<(double)tinsert/CLOCKS_PER_SEC<<","<<(double)tsearch/CLOCKS_PER_SEC<<endl;
		num *= 2;
	}
	return 0;
}
