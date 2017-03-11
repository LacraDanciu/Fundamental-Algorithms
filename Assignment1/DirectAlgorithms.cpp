/* Author : Danciu Diana Lacramioara, group 30421

*  Name : Direct Sorting Algorithms
   Started : 01.03.2016
   Ended: 

*  #Selection Sort - it's a linear algorithm. It's repeatedly picking the smallest to append it the result(the already sorted
* algorithm)
	  - It is extracting the smallest in O(n-i-1)
	  - It's adding it in O(1)
	  - Its complexity is O(n^2)
	  - It's an unstable algorithm
	  - In place algorithm
	  - Additional memory : a variable min for preserving the value

	  #How Selection works  :
	  For example, let's say the whole array is of size 8 and think about how selection sort works.

	  In the first iteration, it has to look at every value in the array, and so the loop body runs 8 times.
	  In the second iteration, it has to look at every value in the subarray from indices 1 to 7, and so the loop body runs 7 times.
	  In the third iteration, it looks at the subarray from indices 2 to 7; the loop body runs 6 times.
	  In the fourth iteration, the subarray from indices 3 to 7; the loop body runs 5 times.
	  …
	  In the eighth and final iteration the loop body runs just 1 time.
	  If we total up the number of times the loop body runs, we get 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 36 times.


	  ##Proof of correctness by loop invariant
	  Loop Invariant:
		Before the start of each loop, A[min] is less than or equal to A[i..j-1]
	  Initialization:
		 Prior to the first iteration of the loop, j=i+1.So the array segment A[i..j-1] is really just spot A[i]. Since line 2 of the code sets
	  min = i, we have that min indexes the smallest element (the only element) in subarray A[i..j-1] and hence the loop invariant is true.
	  Maintenance:
		 Before pass j, we assume that min indexes the smallest element in the subarray A[i..j-1]. During iteration j we have two cases:  either
	  A[j] < A[min] or A[j]>=A[min]. In the second case, the if statement on line 4 is not true, so nothing is executed.  But now min indexes the
	  smallest element of A[i..j]. In the first case, line 5 switches min to index location j since it is the smallest. If min indexes an element
	  less than or equal to subarray A[i..j-1] and now A[j] < A[min],  then it must be the case that A[j] is less than or equal to elements in subarray
	  A[i..j-1]. min switches to index this new location and hence after the loop iteration finishes, min indexes the smallest element in subarray
	  A[i..j].
	  Termination:
		At termination of the inner loop,min indexes an element less than or equal to all elements in subarray A[i..n] since j = n+1 upon termination.
		This finds the smallest element in this subarray and is useful to us in the outer loop because we can move that next smallest item into the correct
		location.

*  #Insertion Sort - maintains a sorted sub-array, and repetitively inserts new elements into it. The process is as following:

	Take the first element as a sorted sub-array.
	Insert the second element into the sorted sub-array (shift elements if needed).
	Insert the third element into the sorted sub-array.
	Repeat until all elements are inserted.

	- It is extracting in O(1)
	- It's adding it in the right place O(n)
	- Its complexity is O(n^2)
	- It's a stable algorithm
	- In place algorithm
	- Additional memory : a variable aux for preserving the value

	##Proof of correctness by loop invariant:
		Input: an array of numbers with length n.
		Output: a non-decreasing reordering of the array

	Step 0:
		find a P first, which is called loop invariant in insertion sort.
		At the start of each iteration of the for loop of line, the sub-array A[1..j-1] consists of the elements originally
		in A[1..j-1] but in sorted order.
	Step 1: 
		Initialization (the base case)
		when j = 2, the sub-array A[1..j-1], consists of A[1], which is obviously sorted.
	Step 2:
		Maintenance (the inductive step)
	Step 3:
		Termination
		The algorithms terminates when j exceeds n, namely j = n+1. So based on the loop invariant, A[1..j-1]=A[1..n] is sorted.

*  #Bubble Sort - repetitively compares adjacent pairs of elements and swaps if necessary.

	Scan the array, swapping adjacent pair of elements if they are not in relative order. This bubbles up the largest element to the end.
	Scan the array again, bubbling up the second largest element.
	Repeat until all elements are in order.
	
	- Its complexity is O(n^2)
	- It's a stable algorithm
	- In place algorithm
	- Additional memory : a variable aux for preserving the value

	##Proof of corectness by loop invariant
	One possible scheme: prove an invariant is true for all iterations
	1.Initialization : the invariant(s) is true prior to the first iteration of the loop
	2.Maintenance: if the invariant is true for iteration n, it is true for iteration n + 1
	3.Termination : when the loop terminates, the invariant is true on the entire input
	For bubblesort, the invariant is "At iteration i , the sub-array A[1..i] is sorted and any element in A[i+1..A.size] is greater or equal
	to any element in A[1..i]

*  #Best case - for 1000 
		#Assignments - for the Selection Sort and Bubble Sort the number of assignments is 0, but for Insertion Sort is 1798
		#Comparisons - for the Selection Sort and BubbleSort the number of comparisons is highly greater than for the Insertion
Sort (404550 to 899)
		#Overall for 1000 in the best case scenario Insertion Sort performs better than Selection Sort and Bubble Sort 
			
			  - for 10000
		#Assignments - Here the difference between the three algorithms is greater. Selection Sort and Bubble Sort remain with
0, but Insertion Sort assignments go to 19798 based on its method of performing the sort. 
		#Comparisons - Here the same difference between Selection Sort, Bubble Sort and Insertion Sort with the number of 
assignments from 49000050 to 9899
		#Overall for 10000 in the best case scenario Insertion Sort performs better than Selection Sort and Bubble Sort

*  #Average case - for 1000
		#Assignments - here the Selection Sort is highly smaller in the number of assignments than Insertion and Selection.
Here we can see the difference in the selection of the minimal elements in comparison to the Bubble Sort method and Insertion
Sort
		#Comparisons - for the comparisons, the Insertion sort is smaller than the other two, Bubble and Selection having the
same number of comparisons
		#Overall for 1000 in the average case Insertion Sort performs better with the smaller amount of operations, followed by
Selection Sort, with a small difference

				 - for 10000 
		#Assignments - here the Selection Sort performs highly better, whereas Bubble Sort has the greater number of assignments.
Insertion Sort is somewhere between those two, but still with a greater number than for Selection Sort
		#Comparisons - for Selection and Bubble Sort the number of comparisons is the same and quite big (49000050) where Insertion
Sort has half number of comparisons of the Selection/Bubble
		#Overall for 10000 Insertion and Selection performs better, with a slight difference between them

*  #Worst case - for 1000
		#Assignments - Selection Sort performs better than the rest with a significant difference, whereas Bubble Sort has the greater
number of assignments and Insertion Sort is in between with least than half of the assignments of Bubble Sort
		#Comparisons - the three algorithms are the same. Bubble and Sort are equal and Insertion has with a few units more comparisons
than the other two
		#Overall for 1000 Selection Sort has the highest performance, whereas Bubble Sort is with the lowest one, followed by Insertion
with a bit higher performance than Bubble (1616922 - Bubble; 810945 - Insertion)

				- for 10000
		#Assignments - exactly the same as for the 1000 case. Just with a higher number of assignments for each case
		#Comparisons - still the same as for the 1000 case. Just a higher number of comparisons for each case
		#Overall for 10000 Selection Sort has the highest performance, with a significant difference between Bubble and Insertion
Selection -	49018602 Insertion - 98019645 Bubble - 195984972

*/

#include "Profiler.h"
#include "stdio.h"

#define MAX_SIZE 10000

Profiler profiler("Direct sorting algorithms");

void Read_Array(int *arr, int n)
{
	int i;

	i = 0;

	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &arr[i]);
	}
}

void Selection_Sort(int *arr, int n)
{
	profiler.countOperation("Selection_assignments", n, 0);
	int i, min, j, aux;

	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			//increasing order
			profiler.countOperation("Selection_comparisons", n);
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			profiler.countOperation("Selection_assignments", n, 3);
			aux = arr[min];
			arr[min] = arr[i];
			arr[i] = aux;
		}
	}
}

void Insertion_Sort(int *arr, int n)
{
	int i, j, aux;

	for (i = 1; i < n; i++)
	{
		profiler.countOperation("Insertion_assignments", n);
		aux = arr[i];
		j = i;

		//increasing order
		profiler.countOperation("Insertion_comparisons", n);
		while ((j > 0) && (arr[j - 1] > aux))
		{
			profiler.countOperation("Insertion_comparisons", n);
			profiler.countOperation("Insertion_assignments", n);
			arr[j] = arr[j - 1];
			j--;
		}
		profiler.countOperation("Insertion_assignments", n);
		arr[j] = aux;
	}
}

void Bubble_Sort(int *arr, int n)
{
	profiler.countOperation("Bubble_Sort_assignments", n, 0);
	int i, j, aux;

	for (i = 0; i < (n - 1); i++)
	{
		for (j = 0; j < (n - i - 1); j++)
		{
			//increasing order
			profiler.countOperation("Bubble_Sort_comparisons", n);
			if (arr[j] > arr[j + 1])
			{
				profiler.countOperation("Bubble_Sort_assignments", n, 3);
				aux = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = aux;
			}
		}
	}
}

void copyArray(int *arr1, int *arr2, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}

}

void BestCase() {
	//variables definition area
	int *ArrayToBeSorted, *b, *c;
	int n;

	//variables initialization area
	ArrayToBeSorted = NULL;
	b = NULL;
	c = NULL;

	//memory allocation area
	ArrayToBeSorted = (int *)malloc(sizeof(int) * MAX_SIZE);
	b = (int *)malloc(sizeof(int) * MAX_SIZE);
	c = (int *)malloc(sizeof(int) * MAX_SIZE);


	//checking allocation area
	if (NULL == ArrayToBeSorted)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == b)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == c)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}


	//let's also measure the execution time
	//the time measurement is not accurate if we also count operations
	// profiler.disableCounters();
	for (n = 100; n < MAX_SIZE; n += 100) {

		FillRandomArray(ArrayToBeSorted, n, 100, MAX_SIZE, false, 1);
		copyArray(ArrayToBeSorted, b, n);
		copyArray(ArrayToBeSorted, c, n);
		Insertion_Sort(ArrayToBeSorted, n);
		Selection_Sort(b, n);
		Bubble_Sort(c, n);
	}

	profiler.createGroup("Assignments", "Selection_assignments", "Insertion_assignments", "Bubble_Sort_assignments");
	profiler.createGroup("Comparisons", "Selection_comparisons", "Insertion_comparisons", "Bubble_Sort_comparisons");
	profiler.addSeries("selection", "Selection_assignments", "Selection_comparisons");
	profiler.addSeries("insertion", "Insertion_assignments", "Insertion_comparisons");
	profiler.addSeries("bubble", "Bubble_Sort_assignments", "Bubble_Sort_comparisons");
	profiler.createGroup("Best Case Scenario", "selection", "insertion", "bubble");

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

	if (NULL != c)
	{
		free(c);
		c = NULL;
	}
}


void AverageCase() {
	//variables definition area
	int *ArrayToBeSorted, *b, *c;
	int i, n;

	//variables initialization area
	ArrayToBeSorted = NULL;
	b = NULL;
	c = NULL;
	i = 0;

	//memory allocation area
	ArrayToBeSorted = (int *)malloc(sizeof(int) * MAX_SIZE);
	b = (int *)malloc(sizeof(int) * MAX_SIZE);
	c = (int *)malloc(sizeof(int) * MAX_SIZE);


	//checking allocation area
	if (NULL == ArrayToBeSorted)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == b)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == c)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}


	//let's also measure the execution time
	//the time measurement is not accurate if we also count operations
	// profiler.disableCounters();
	for (n = 100; n < MAX_SIZE; n += 100) {
		for (i = 0; i < 5; i++) {

			FillRandomArray(ArrayToBeSorted, n);
			copyArray(ArrayToBeSorted, b, n);
			copyArray(ArrayToBeSorted, c, n);
			Insertion_Sort(ArrayToBeSorted, n);
			Selection_Sort(b, n);
			Bubble_Sort(c, n);
		}
	}

	profiler.createGroup("Assignments", "Selection_assignments", "Insertion_assignments", "Bubble_Sort_assignments");
	profiler.createGroup("Comparisons", "Selection_comparisons", "Insertion_comparisons", "Bubble_Sort_comparisons");
	profiler.addSeries("selection", "Selection_assignments", "Selection_comparisons");
	profiler.addSeries("insertion", "Insertion_assignments", "Insertion_comparisons");
	profiler.addSeries("bubble", "Bubble_Sort_assignments", "Bubble_Sort_comparisons");
	profiler.createGroup("Average Case Scenario 1000", "selection", "insertion", "bubble");
	profiler.createGroup("Assignments for Selections", "Selection_assignments");

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

	if (NULL != c)
	{
		free(c);
		c = NULL;
	}
}

void WorstCase() {
	//variables definition area
	int *ArrayToBeSorted, *b, *c;
	int n;

	//variables initialization area
	ArrayToBeSorted = NULL;
	b = NULL;
	c = NULL;

	//memory allocation area
	ArrayToBeSorted = (int *)malloc(sizeof(int) * MAX_SIZE);
	b = (int *)malloc(sizeof(int) * MAX_SIZE);
	c = (int *)malloc(sizeof(int) * MAX_SIZE);


	//checking allocation area
	if (NULL == ArrayToBeSorted)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == b)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}

	if (NULL == c)
	{
		printf_s("Malloc failed with error %d at line %d in the file %s \n", GetLastError(), __LINE__, __FILE__);
	}


	//let's also measure the execution time
	//the time measurement is not accurate if we also count operations
	// profiler.disableCounters();
	for (n = 100; n < MAX_SIZE; n += 100) {

		FillRandomArray(ArrayToBeSorted, n, 100, MAX_SIZE, false, 2);
		copyArray(ArrayToBeSorted, b, n);
		copyArray(ArrayToBeSorted, c, n);
		Insertion_Sort(ArrayToBeSorted, n);
		Selection_Sort(b, n);
		Bubble_Sort(c, n);
	}

	profiler.createGroup("Assignments", "Selection_assignments", "Insertion_assignments", "Bubble_Sort_assignments");
	profiler.createGroup("Comparisons", "Selection_comparisons", "Insertion_comparisons", "Bubble_Sort_comparisons");
	profiler.addSeries("selection", "Selection_assignments", "Selection_comparisons");
	profiler.addSeries("insertion", "Insertion_assignments", "Insertion_comparisons");
	profiler.addSeries("bubble", "Bubble_Sort_assignments", "Bubble_Sort_comparisons");
	profiler.createGroup("Worst Case Scenario", "selection", "insertion", "bubble");

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

	if (NULL != c)
	{
		free(c);
		c = NULL;
	}
}

int main()
{
	//BestCase();
	//AverageCase();
	WorstCase();
	return (0);
}