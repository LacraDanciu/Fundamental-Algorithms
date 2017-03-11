/************************************************************************/
/* Student: Danciu Diana Lacramioara
   Group: 30421

   Bottom up - when you already know the elements and the tree is formed
   Top down - when you know the elements only at runtime. We start with an empty tree. 

   The HEAPIFY procedure, which runs in O(lg n) time, is the key to maintaining the max-heap property.
   The BUILD-MAX-HEAP procedure, which runs in linear time, produces a maxheap from an unordered input array.
   The HEAPSORT procedure, which runs in O(n lg n) time, sorts an array in place.
   The MAX-HEAP-INSERT, HEAP-EXTRACT-MAX, HEAP-INCREASE-KEY, and HEAP-MAXIMUM procedures, which run in O(lg n) time, allow the heap
   data structure to implement a priority queue.

   In order to maintain the max-heap property, we call the procedure HEAPIFY.
   Its inputs are an array A and an index i into the array. When it is called, HEAPIFY assumes that the binary trees rooted at LEFT.i / and RIGHT.i / are maxheaps,
   but that A[i] might be smaller than its children, thus violating the max-heap property.
   HEAPIFY lets the value at A[i] “float down” in the max-heap so that the subtree rooted at index i obeys the max-heap property.

   The running time of HEAPIFY on a subtree of size n rooted at a given node i is the ‚.1/ time to fix up the relationships among the elements A[i],
   A[LEFT(i)], and A[RIGHT(i)], plus the time to run HEAPIFY on a subtree  rooted at one of the children of node i (assuming that the recursive call occurs).
   The children’s subtrees each have size at most 2n=3—the worst case occurs when the bottom level of the tree is exactly half full

   BUIL-HEAP makes O(n) calls.

##BottomUp Method -> Put everything in the array and then heapify/fix the trees in a bottom-up way. 
	Build an essentially complete binary tree by inserting n keys in the given order.
	Heapify a series of trees
		Starting with the last (rightmost) parental node, heapify/fix the subtree rooted at it:
		if the parental dominance condition does not hold for the key at this node:
			1. exchange its key K with the key of its larger child
			2. Heapify/fix the subtree rooted at it (now in the child’s position)
		Proceed to do the same for the node’s immediate predecessor.
		Stops after this is done for the tree’s root.
		Example: 4 1 3 2 16 9 10 14 8 7 16 14 10 8 7 9 3 2 4 1 5 

   Total Heap Construction Cost
		For h=1: C1= 2
		For h=2: C2= 2C1+ 2*2
		For h: Ch= 2Ch-1+ 2h
		Total cost: Doubles with h (plus a small constant factor): Exponential in h
		Total cost: Linear in N

	Order of growth of running time
		Heap construction: N
	for heap sort: N calls to delete max: N log N
	Total Extra Space
		Constant (in-place)

		Worst case:
		 -> a full tree;each key on a certain level will travel to the leaf.
			- Fix a subtree rooted at height j: 2j comparisons
			- Fix a subtree rooted at level i : 2(h-i) comparisons
				A node’s level + its height = h, the tree’s height.
			- Total for heap construction phase: from i=0 to h-1 ?2*(h-i)*2^i = 2*(n – lg*(n + 1)) = ?(n) (2^i = nodes at level i)
		
		#For the decreasing array, bottom-up goes only on half of the interval, 2 comparisons on iterations and doesn't make any assignments
	because it doesn't find what to change.
*******************************************************************************************************************************************************
	A priority queue is a data structure for maintaining a set S of elements, each with an associated value called a key.
	A max-priority queue supports the following operations:
	INSERT (S, x) inserts the element x into the set S
	MAXIMUM(S) returns the element of S with the largest key.
	EXTRACT-MAX(S) removes and returns the element of S with the largest key.
	INCREASE-KEY(S, x, k) increases the value of element x’s key to the new value k, which is assumed to be at least as large as x’s current key value.

	The running time of MAX-HEAP-INSERT on an n-element heap is O(lg n)
	In summary, a heap can support any priority-queue operation on a set of size n in O(lg n) time.

#TopDown Method - Heaps can be constructed by successively inserting elements into an (initially) empty heap
		Algorithm:
			Insert element at the last position in heap.
			Compare with its parent, and exchange them if it violates the parental dominance condition.
			Continue comparing the new element with nodes up the tree until the parental dominance condition is satisfied.
		Efficiency:
			O(nlogn) in the worst case 
			Usually is actually O(n)
			Inserting one new element to a heap with n-1 nodes requires no more comparisons than the heap’s height
		Worst case : O(nlogn)

   Started: 08.03.2016
   Ended: 15.03.2016
*/
/********************************************************************************************************************/

#include "Profiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#define MAX_SIZE 10001
#define MAX_INFINITE 10001

using namespace std;

Profiler profiler("HEAP_SORT algorithm");

int n, max_size;

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
	profiler.countOperation("BottomUpAssignments", n, 0);
	int left, right, largest, aux;

	left = 2 * i;
	right = 2 * i + 1;

	profiler.countOperation("BottomUp", n, 1);
	profiler.countOperation("BottomUpComparisons", n, 1);
	if ((left <= max_size) && (arr[left] > arr[i]))
	{
		largest = left;
	}
	else
	{
		largest = i;
	}

	profiler.countOperation("BottomUpComparisons", n, 1);
	profiler.countOperation("BottomUp", n, 1);
	if ((right <= max_size) && (arr[right] > arr[largest]))
	{

		largest = right;
	}

	if (largest != i)
	{
		profiler.countOperation("BottomUp", n, 3);
		profiler.countOperation("BottomUpAssignments", n, 3);
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

	for (i = n / 2; i >= 1; i--)
	{
		heapify(a, i);
	}
}

/// Top down method
void increase_key(int a[MAX_SIZE], int i, int key)
{
	profiler.countOperation("TopDownComparisons", n, 0);
	int aux;

	a[i] = key;
	profiler.countOperation("TopDown", n, 1);
	profiler.countOperation("TopDownAssignments", n, 1);

	profiler.countOperation("TopDown", n, 1);
	profiler.countOperation("TopDownComparisons", n, 1);
	while (i > 1 && a[i / 2] < a[i])
	{
		profiler.countOperation("TopDown", n, 1);
		profiler.countOperation("TopDownComparisons", n, 1);

		profiler.countOperation("TopDown", n, 3);
		profiler.countOperation("TopDownAssignments", n, 3);
		aux = a[i];
		a[i] = a[i / 2];
		a[i / 2] = aux;

		i = i / 2;
	}
}

void insert(int a[MAX_SIZE], int key)
{
	max_size++;
	profiler.countOperation("TopDownAssignments", n, 1);
	a[max_size] = -MAX_INFINITE;
	increase_key(a, max_size, key);
}

void build_heap_top_down(int a[MAX_SIZE])
{
	max_size = 1;
	for (int i = 2; i <= n; i++)
	{
		insert(a, a[i]);
	}
}

//void heapsort(int a[MAX_SIZE])
//{
//  int aux;
//	buildHeapTopDown(a);
//	for (int i = n; i >= 2; i--)
//	{
//		aux = a[1];
//		a[1] = a[i];
//		a[i] = aux;
//		profiler.countOperation("HeapSort", n, 3);
//		max_size--;
//		heapify(a, 1);
//
//	}
//}

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
			build_heap_bottom_up(ArrayToBeSorted);

			build_heap_top_down(b);
		}
	}

	profiler.createGroup("Assignments", "TopDownAssignments", "BottomUpAssignments");
	profiler.createGroup("Comparisons", "TopDownComparisons", "BottomUpComparisons");
	profiler.createGroup("Overall average case HEAP_SORT", "TopDown", "BottomUp");

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
		FillRandomArray(ArrayToBeSorted, n, 100, MAX_SIZE, false, 1); //because I'm building them decreasing
		copy_array(ArrayToBeSorted, b);
		build_heap_bottom_up(ArrayToBeSorted);
		build_heap_top_down(b);
	}

	profiler.createGroup("Assignments", "TopDownAssignments", "BottomUpAssignments");
	profiler.createGroup("Comparisons", "TopDownComparisons", "BottomUpComparisons");
	profiler.createGroup("Overall worst case HEAP_SORT", "TopDown", "BottomUp");

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

int main()
{
	AverageCase();
	//WorstCase();
	return (0);
}