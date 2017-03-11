/*************************************************************************************************************/
/* Danciu Diana Lacramioara
* Group 30421
* Started date: 22.03.2016
* Ended date: 29.03.2016

* Merging k ordered lists was following this principle : single linked lists and a heap were used as
* data structures. The initial heap(minHeap) was built with the first element from each list.Then,the minHeapify
* procedure was applied for the current heap.

* At each step,the first(the smallest) element from the heap was popped and replaced with the next element from
* the list it was chosen.If there are no more elements in the list,the first element from the heap is replaced with
* the rightmost child(the last element from the heap) and the size of the heap is decreased.The result after each
* pop is stored in a linked list.

* In the first case,the running time of the algorithm takes as follows:each call to minHeapify takes lg k,each of the n elements
* from the lists is inserted and popped from the heap.It results in a total running time of O(n log k).

* In the second case,the running time of the algorithm is lg k, since n is a constant.

*** Proof: Consider the following loop invariant: The i-th element to insert into result is always the minimum of the min-heap H in step i and therefore,
* result[1..i] is correctly sorted after the i-th iteration.
* This is true before the first iteration: First, we show that the first element to insert into result is in H:
* Assume towards a contradiction that the first element to insert into result (that is, the overall smallest element, call it r1) were not a first element.
* Then, in the list l that contains r1, the first element l[1] must be distinct from r1 (as by assumption, r1 is not a first element).
* As our lists are all sorted, we have even l[1]<r1, but this is a contradiction, as we chose r1 to be the overall smallest element.
* Obviously, the minimum of all first elements is the one to insert into result.
* The invariant holds after an iteration: We proceed in the same way. Assume the i-th element to insert (call it ri) were not in H.
* By construction, H holds at most one element from each list, and once it contains an element m from a list l,
* all of its predecessors in l were already extracted from H and (by hypothesis) correctly inserted into result.
* Therefore, ri is assumed to be a successor of some element m in the list l. But this is, as above, a contradiction,
* as l is sorted, and therefore, the invariant holds. On termination, we thus have result[1..n] correctly sorted.

*****************************************************************************************************************/

#include<iostream>
#include<conio.h>
#include "Profiler.h"
#define MAX_SIZE 10000
#define MINUS_INFINITE -10000

Profiler p("MergeKSortedLists");

typedef struct Node
{
	struct Node *next;
	int data;

}NodeT;

typedef struct
{
	int size;
	NodeT *first;
	NodeT *last;
}HeaderT;

typedef struct
{
	int listIndex;
	int key;
}HeapT;

HeaderT *create_list()
{
	HeaderT *aux = (HeaderT *)malloc(sizeof(HeaderT));
	if (aux)
	{
		aux->size = 0;
		aux->first = NULL;
		aux->last = NULL;
	}

	return aux;
}

NodeT *create_Node(int data)
{
	NodeT *aux = (NodeT *)malloc(sizeof(NodeT));
	if (aux)
	{
		aux->next = NULL;
		aux->data = data;
	}
	return aux;
}

int insert_Node(HeaderT *list, NodeT *pNode)
{
	if ((!list) || (!pNode))
	{
		return (0);
	}
	if (list->first == NULL)
	{
		list->first = pNode;
		list->last = pNode;
		pNode->next = NULL;
		list->size++;
		return (1);
	}
	else
	{
		list->last->next = pNode;
		list->last = pNode;
		list->last->next = NULL;
		list->size++;
		return (1);
	}
}

int delete_first(HeaderT *list)
{
	if (!list)
	{
		return (0);
	}

	NodeT *aux = list->first;

	if (!aux)
	{
		return (0);
	}
	list->first = aux->next;
	list->size--;

	return (aux->data);
}

void print_list(HeaderT *list)
{
	NodeT *aux = (NodeT *)malloc(sizeof(NodeT));

	if (!list)
	{
		return;
	}

	aux = list->first;

	while (aux)
	{
		printf("%d ", aux->data);
		aux = aux->next;
	}
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(HeapT **a, int size, int index, char total[], int n, int sizeOfProfiler)
{
	int largest;
	int left;
	int right;

	largest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;

	p.countOperation(total, sizeOfProfiler, 1);
	if ((left < size) && ((a[left]->key) < (a[largest]->key)))
	{
		largest = left;
	}
	p.countOperation(total, sizeOfProfiler, 1);
	if ((right < size) && ((a[right]->key) < (a[largest]->key)))
	{
		largest = right;
	}
	if (largest != index)
	{
		swap(&a[index]->key, &a[largest]->key);
		swap(&a[index]->listIndex, &a[largest]->listIndex);
		p.countOperation(total, sizeOfProfiler, 3);
		heapify(a, size, largest, total, n, sizeOfProfiler);
	}

}

void build_heap_bottom_up(HeapT **a, int size, char total[], int n, int sizeOfProfiler)
{
	for (int i = (size - 1) / 2; i >= 0; i--)
	{
		heapify(a, size, i, total, n, sizeOfProfiler);
	}
}

void merge_lists(HeaderT *list[], HeapT **a, int size, int k, HeaderT *result, char total[], int sizeOfProfiler)
{
	for (int i = 0; i < k; i++)
	{
		a[i]->key = delete_first(list[i]);
		a[i]->listIndex = i;
		p.countOperation(total, sizeOfProfiler, 1);
	}

	build_heap_bottom_up(a, k, total, size, sizeOfProfiler);

	int temp = size - 1;
	int temp1 = 0;

	while (temp >= 0)
	{
		NodeT *auxP = create_Node(a[0]->key);
		insert_Node(result, auxP);
		p.countOperation(total, sizeOfProfiler, 1);

		if ((list[a[0]->listIndex]->size == 0) && (k > 0))
		{
			a[0]->key = a[k - 1]->key;
			a[0]->listIndex = a[k - 1]->listIndex;
			p.countOperation(total, sizeOfProfiler, 1);
			k--;
		}
		else
		{
			a[0]->key = delete_first(list[a[0]->listIndex]);
			p.countOperation(total, sizeOfProfiler, 1);
		}

		heapify(a, k, 0, total, size, sizeOfProfiler);
		temp--;
	}
}

void merge_test(HeaderT *list[], HeapT **c, int arr[], int k, HeaderT *result, char total[])
{
	for (int size = 100; size <= 10000; size += 100)
	{
		for (int i = 0; i < k; i++)
		{
			c[i] = (HeapT*)malloc(sizeof(HeapT));
			list[i] = create_list();
			FillRandomArray(arr, size / k, 10, 50000, false, 1);
			for (int j = 0; j < size / k; j++)
			{
				NodeT*p = create_Node(arr[j]);
				insert_Node(list[i], p);
			}
		}

		merge_lists(list, c, size, k, result, total, size);
	}
}

void merge_for_fixed_size(HeaderT *list[], HeapT **c, int arr[], int n, HeaderT *result, char total[])
{
	for (int k = 10; k <= 500; k += 10)
	{
		for (int i = 0; i < k; i++)
		{
			c[i] = (HeapT*)malloc(sizeof(HeapT));
			list[i] = create_list();
			FillRandomArray(arr, n / k, 10, 50000, false, 1);
			for (int j = 0; j < n / k; j++)
			{
				NodeT* p = create_Node(arr[j]);
				insert_Node(list[i], p);
			}
		}
		merge_lists(list, c, n, k, result, total, k);
	}
}

int main()
{
	HeaderT *list[MAX_SIZE];
	int a[MAX_SIZE];
	HeapT *c[MAX_SIZE];
	HeaderT *result;
	int k = 4;
	int n = 10000;
	int size = 20;

	printf("%s", "The initial lists are:\n\n");

	for (int i = 0; i < k; i++)
	{
		c[i] = (HeapT*)malloc(sizeof(HeapT));
		list[i] = create_list();
		FillRandomArray(a, size / k, 10, 50000, false, 1);
		for (int j = 0; j < size / k; j++)
		{
			NodeT*p = create_Node(a[j]);
			insert_Node(list[i], p);
		}
	}

	for (int i = 0; i < k; i++)
	{
		printf("%s%d", "List number ", i + 1);
		printf(":");
		print_list(list[i]);
		printf("\n");
	}
	result = create_list();
	merge_lists(list, c, size, k, result, "Demo", size);

	printf("%s", "\nThe sorted array is:\n ");

	print_list(result);

	int k1 = 5;
	merge_test(list, c, a, k1, result, "Total for 5 lists");
	int k2 = 10;
	merge_test(list, c, a, k2, result, "Total for 10 lists");
	int k3 = 100;
	merge_test(list, c, a, k3, result, "Total for 100 lists");

	p.createGroup("First", "Total for 5 lists", "Total for 10 lists", "Total for 100 lists");

	merge_for_fixed_size(list, c, a, n, result, "Total for size 10000");

	p.showReport();

	return (0);
}