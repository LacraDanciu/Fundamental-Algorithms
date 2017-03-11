/************************************************************************/
/*
OBS:
The most direct competitor of quicksort is heapsort. Heapsort is typically somewhat slower than quicksort, but the worst-case running time is always ?(nlogn).
Quicksort is usually faster, though there remains the chance of worst case performance except in the introsort variant, which switches to heapsort when a bad case is detected.
If it is known in advance that heapsort is going to be necessary, using it directly will be faster than waiting for introsort to switch to it.


Heapsort is a comparison-based sorting algorithm.
Heapsort can be thought of as an improved selection sort: like that algorithm,
it divides its input into a sorted and an unsorted region,
and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region.
The improvement consists of the use of a heap data structure rather than a linear-time search to find the maximum.

Heapsort is O(N log N) guaranted, what is much better than worst case in Quicksort.
Heapsort don't need more memory for another array to putting ordered data as is needed by Mergesort.
So why do comercial applications stick with Quicksort? What Quicksort has that is so special over others implementations?

I've tested the algorithms myself and I've seen that Quicksort has something special indeed.
It runs fast, much faster than Heap and Merge algorithms.

The secret of Quicksort is: It almost doesn't do unnecessary element swaps. Swap is time consuming.

With Heapsort, even if all of your data is already ordered, you are going to swap 100% of elements to order the array.

With Quicksort you don't swap what is already ordered.
If your data is completely ordered, you swap almost nothing!
Although there is a lot of fussing about worst case, a little improvement on the choice of pivot, any other than getting the first or last element of array, can avoid it.
If you get a pivot from the intermediate element between first, last and middle element, it is suficient to avoid worst case.

What is superior in Quicksort is not the worst case, but the best case!
In best case you do the same number of comparisons, ok, but you swap almost nothing.
In average case you swap part of the elements, but not all elements, as in Heapsort.
That is what gives Quicksort the best time. Less swap, more speed.


####Quick Select
Statement:
*   Given a list of values, find the highest kth. Assume indexing starts
*   at one and not at zero so that the greatest number in the list is
*   the 1st and not the 0th number.
*
* Time Complexity: average = O(n log n); worse O(n^2)
*
* Sample Input: {21,3,34,5,13,8,2,55,1,19}; 4
* Sample Output: 19
*
* Details: This is a selection algorithm, where the task is to select
*   an elite out of a group. In the sample input, for instance, we are
*   to select the 4th greatest number in the list; which happens to be 13
*   since 55, 34, and 21 are all greater than 13.
*
*   Generally, selection algorithms are modified sort algorithms; where
*   instead of sorting the whole list, we sort up to the kth value.
*   Hence, a selection algorithm is bounded by whatever sort algorithm
*   is used to implement it.
*
*   Here for example we are using quickselect to find the kth largest
*   value. Consequently, this algorithm is bounded by quicksort; leading
*   to a worse case time complexity of O(n^2) and an average case
*   time complexity of O( n log n).
*
*   Note: Finding the kth largest is essentially the same as finding
*   the kth smallest.

*/
/************************************************************************/

#include "Profiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#define MAX_SIZE 10000

using namespace std;

int n, max_size;

Profiler profiler("HEAP_SORT Vs QUICK_SORT algorithm");

void copy_array(int *arr1, int *arr2)
{
	int i;

	for (i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}

}

// Bottom up method
void heapify(int arr[MAX_SIZE], int i)
{
	profiler.countOperation("HeapSortAssignments", n, 0);
	int left, right, largest, aux;

	left = 2 * i;
	right = 2 * i + 1;

	profiler.countOperation("HeapSort", n, 1);
	profiler.countOperation("HeapSortComparisons", n, 1);
	if ((left < max_size) && (arr[left] > arr[i]))
	{
		largest = left;
	}
	else
	{
		largest = i;
	}

	profiler.countOperation("HeapSortComparisons", n, 1);
	profiler.countOperation("HeapSort", n, 1);
	if ((right < max_size) && (arr[right] > arr[largest]))
	{

		largest = right;
	}

	if (largest != i)
	{
		profiler.countOperation("HeapSort", n, 1);
		profiler.countOperation("HeapSortAssignments", n, 3);
		aux = arr[i];
		arr[i] = arr[largest];
		arr[largest] = aux;

		heapify(arr, largest);
	}
}

void build_heap_bottom_up(int a[MAX_SIZE])
{
	max_size = n;
	int i;

	for (i = (n - 1) / 2; i >= 0; i--)
	{
		heapify(a, i);
	}
}

void heapsort(int a[MAX_SIZE])
{
	int aux;
	build_heap_bottom_up(a);
	for (int i = n - 1; i >= 1; i--)
	{
		aux = a[0];
		a[0] = a[i];
		a[i] = aux;
		profiler.countOperation("HeapSort", n, 3);
		profiler.countOperation("HeapSortAssignments", n, 0);
		max_size--;
		heapify(a, 0);
	}
}

void quicksort(int *a, int first, int last, int size)
{
	int pivot, j, temp, i;// aux;

	if (first < last)
	{
		// for best case
		/*aux = a[first];
		a[first] = a[(first + last) / 2];
		a[(first + last) / 2] = aux;*/

		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			profiler.countOperation("QuickSort", size, 1);
			profiler.countOperation("QuickSortComparisons", n, 1);
			while (a[i] <= a[pivot] && i < last)
			{
				profiler.countOperation("QuickSort", size, 1);
				profiler.countOperation("QuickSortComparisons", size, 1);
				i++;
			}
			profiler.countOperation("QuickSort", size, 1);
			profiler.countOperation("QuickSortComparisons", size, 1);
			while (a[j] > a[pivot])
			{
				profiler.countOperation("QuickSort", size, 1);
				profiler.countOperation("QuickSortComparisons", size, 1);
				j--;
			}
			if (i < j)
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
				profiler.countOperation("QuickSort", size, 3);
				profiler.countOperation("QuickSortAssignments", size, 3);
			}
		}

		temp = a[pivot];
		a[pivot] = a[j];
		a[j] = temp;
		profiler.countOperation("QuickSort", size, 3);
		profiler.countOperation("QuickSortAssignments", size, 3);
		quicksort(a, first, j - 1, size);
		quicksort(a, j + 1, last, size);
	}
}

int quick_select(int *a, int len, int k)
{
	int i, st, aux;

	for (st = i = 0; i < len - 1; i++)
	{
		if (a[i] > a[len - 1])
		{
			continue;
		}
		aux = a[i];
		a[i] = a[st];
		a[st] = aux;
		st++;
	}
	aux = a[len - 1];
	a[len - 1] = a[st];
	a[st] = aux;
	return (k == st ? a[st] : st > k ? quick_select(a, st, k) : quick_select(a + st, len - st, k - st));
}

void BestCase() {
	//variables definition area
	int *ArrayToBeSorted, *b;

	//variables initialization area
	ArrayToBeSorted = NULL;
	b = NULL;

	//memory allocation area
	ArrayToBeSorted = (int *)malloc(sizeof(int) * MAX_SIZE);
	b = (int *)malloc(sizeof(int) * MAX_SIZE);

	//checking allocation area
	if (NULL == ArrayToBeSorted)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == b)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	for (n = 100; n < 10000; n += 100) {
		FillRandomArray(ArrayToBeSorted, n, 100, MAX_SIZE, false, 1);
		quicksort(ArrayToBeSorted, 0, n - 1, n);
	}

	profiler.createGroup("Assignments", "QuickSortAssignments");
	profiler.createGroup("Comparisons", "QuickSortComparisons");
	profiler.createGroup("Overall best case", "QuickSort");

	profiler.showReport(1);

Cleanup:
	if (NULL != ArrayToBeSorted)
	{
		free(ArrayToBeSorted);
		ArrayToBeSorted = NULL;
	}

	if (NULL != b)
	{
		free(b);
		b = NULL;
	}
}

void AverageCase()
{
	//variables definition area
	int *ArrayToBeSorted, *b;
	int i;

	//variables initialization area
	ArrayToBeSorted = NULL;
	b = NULL;
	i = 0;

	//memory allocation area
	ArrayToBeSorted = (int *)malloc(sizeof(int) * MAX_SIZE);
	b = (int *)malloc(sizeof(int) * MAX_SIZE);

	//checking allocation area
	if (NULL == ArrayToBeSorted)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == b)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	for (n = 100; n < 10000; n += 100) {
		for (i = 0; i < 5; i++) {
			FillRandomArray(ArrayToBeSorted, n);
			copy_array(ArrayToBeSorted, b);
			heapsort(ArrayToBeSorted);
			quicksort(b, 0, n - 1, n);
		}
	}

	profiler.createGroup("Assignments", "QuickSortAssignments", "HeapSortAssignments");
	profiler.createGroup("Comparisons", "QuickSortComparisons", "HeapSortComparisons");
	profiler.createGroup("Overall average case", "QuickSort", "HeapSort");

	profiler.showReport(5);

Cleanup:
	if (NULL != ArrayToBeSorted)
	{
		free(ArrayToBeSorted);
		ArrayToBeSorted = NULL;
	}

	if (NULL != b)
	{
		free(b);
		b = NULL;
	}
}

void WorstCase() {
	//variables definition area
	int *ArrayToBeSorted, *b;

	//variables initialization area
	ArrayToBeSorted = NULL;
	b = NULL;

	//memory allocation area
	ArrayToBeSorted = (int *)malloc(sizeof(int) * MAX_SIZE);
	b = (int *)malloc(sizeof(int) * MAX_SIZE);

	//checking allocation area
	if (NULL == ArrayToBeSorted)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == b)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	for (n = 100; n < 10000; n += 100) {
		FillRandomArray(ArrayToBeSorted, n, 100, MAX_SIZE, false, 1);
		copy_array(ArrayToBeSorted, b);
		quicksort(ArrayToBeSorted, 0, n - 1, n);
	}

	profiler.createGroup("Assignments", "QuickSortAssignments");
	profiler.createGroup("Comparisons", "QuickSortComparisons");
	profiler.createGroup("Overall worst case", "QuickSort");

	profiler.showReport(1);

Cleanup:
	if (NULL != ArrayToBeSorted)
	{
		free(ArrayToBeSorted);
		ArrayToBeSorted = NULL;
	}

	if (NULL != b)
	{
		free(b);
		b = NULL;
	}
}

void TestQuickSort()
{
#define N (sizeof(arr)/sizeof(arr[0]))

	//variables definition area
	int arr[] = {9, 8, 7, 6, 5, 0, 1, 2, 3, 4};
	int arr2[N];

	int i;
	for (i = 0; i < 10; i++) {
		memcpy(arr2, arr, sizeof(arr)); // quick_select modifies array
		printf("%d: %d\n", i, quick_select(arr2, 10, i));
	}

	quicksort(arr, 0, 9, 10);
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	//BestCase();
	//AverageCase();
	WorstCase();
	//TestQuickSort();
	return (0);
}
