/**************************************************************************************************************************************/
/*
	Student : Diana Lacramioara Danciu
	Group: 30421

	A disjoint-set data structure maintains a collection S ={S1; S2; : : : ;Sk} of disjoint
	dynamic sets. We identify each set by a representative, which is some member
	of the set. In some applications, it doesn’t matter which member is used as the
	representative; we care only that if we ask for the representative of a dynamic set
	twice without modifying the set between the requests, we get the same answer both
	times. Other applications may require a prespecified rule for choosing the representative,
	such as choosing the smallest member in the set (assuming, of course,
	that the elements can be ordered).

	The procedure CONNECTED-COMPONENTS initially places each vertex in its
	own set. Then, for each edge .u; /, it unites the sets containing u and . By
	Exercise 21.1-2, after processing all the edges, two vertices are in the same connected
	component if and only if the corresponding objects are in the same set.
	Thus, CONNECTED-COMPONENTS computes sets in such a way that the procedure
	SAME-COMPONENT can determine whether two vertices are in the same connected component.

	In an actual implementation of this connected-components algorithm, the representations
	of the graph and the disjoint-set data structure would need to reference
	each other. That is, an object representing a vertex would contain a pointer to
	the corresponding disjoint-set object, and vice versa. 

	What is the priority queue? E sorted.
	What is the maximum number of finds? m = |E| finds
	What is the maximum number of unions? n = |V| unions, because only n vertices are added to the minimum spanning tree.
	So there are at most m find and n unions.

	The total cost is the cost of making the priority queue of edges (sorting E) and the disjoint set finds and unions.
	If the implementation of disjoint sets are trees with path compression, the cost of the of the disjoint set finds and unions are O(n + m)
	Note that for a connected graph n ε O(m), disjoint sets operations are bounded by O(m).

	Then the total cost of Kruskal's algorithm it is bounded by sorting the edges, O(m lg m) for a connected graph.

*/
#include<conio.h>
#include "Profiler.h"
#include <stdlib.h>

Profiler p("DisjointSets");

int n;

void make_set(int x, int *parent, int *weights, int size)
{
	parent[x] = x;
	weights[x] = 0;
	p.countOperation("TotalOperations", n, 1);
}

void link(int x, int y, int *parent, int *weights, int size)
{
	p.countOperation("TotalOperations", n, 1);
	if (weights[x] > weights[y])
	{
		p.countOperation("TotalOperations", n, 1);
		parent[y] = x;
	}
	else
	{
		p.countOperation("TotalOperations", n, 2);
		parent[x] = y;
		if (weights[x] == weights[y])
		{
			p.countOperation("TotalOperations", n, 1);
			weights[y] = weights[y] + 1;
		}
	}
}

int find_set(int x, int *parent, int size)
{
	if (x != parent[x])
	{
		p.countOperation("TotalOperations", n, 1);
		parent[x] = find_set(parent[x], parent, size);
	}
	return (parent[x]);
}

void union_set(int x, int y, int *parent, int *weights, int size)
{
	p.countOperation("TotalOperations", n, 1);
	link(find_set(x, parent, size), find_set(y, parent, size), parent, weights, size);
}

void Kruskal(int edges, int vertices, int **e)
{
	int *parent, *weights;
	int i, j;

	parent = NULL;
	weights = NULL;

	parent = (int*)calloc(vertices, sizeof(int));
	weights = (int*)calloc(vertices, sizeof(int));

	if (parent == NULL)
	{
		printf("Malloc failed!\n");
	}

	if (weights == NULL)
	{
		printf("Malloc failed!\n");
	}

	for (i = 0; i < vertices; i++)
	{
		make_set(i, parent, weights, edges);
	}

	for (j = 0; j < edges; j++)
	{	
		if (find_set(e[j][0], parent, edges) != find_set(e[j][1], parent, edges))
		{
			union_set(e[j][0], e[j][1], parent, weights, edges);
		}
	}

	free(parent);
	free(weights);
}


int main()
{
	int **e;
	int edges, j, k;
	
	for (n = 100; n <= 10000; n += 100)
	{
		edges = n * 4;

		e = NULL;
		e = (int **)malloc(sizeof(int*) * edges);

		for (j = 0; j < edges; j++)
		{
			e[j] = (int*)malloc(sizeof(int) * 3);
		}

		if (e == NULL)
		{
			printf("Malloc failed!\n");
		}

		//first edges/4
		for (j = 1; j <= (edges / 4) - 1; j++)
		{
			e[j - 1][0] = j - 1; // source
			e[j - 1][1] = j; // destination
			e[j - 1][2] = rand() % 100; // weight
		}

		// from egdes /4 until end
		for (j = (edges / 4)-1; j < edges; j++)
		{
			e[j][0] = rand() % n;

			e[j][1] = rand() % n;

			e[j][2] = rand() % 100;
		}

		//sort based on the weights using bubble sort
		for (j = 0; j < edges - 1; j++)
		{
			for (k = j + 1; k < edges; k++)
			{
				p.countOperation("TotalOperations", n, 1);
				if (e[j][3] > e[k][3])
				{
					//swap
					p.countOperation("TotalOperations", n, 3);
					int aux = e[j][3];
					e[j][3] = e[k][3];
					e[k][3] = aux;
				}
			}
		}

		Kruskal((n * 4), n, e);

		free(e);
	}

	/* TEST
	n = 10;
	edges = 5;
	e[edges][3];
	for (j = 0; j < (edges / 4) - 1; j++)
	{
		e[j - 1][0] = j - 1; // source
		e[j - 1][1] = j; // destination
		e[j - 1][2] = rand() % 10; // weight
	}

	for (j = (edges / 4) - 1; j < edges; j++)
	{
		e[j][0] = rand() % n;

		e[j][1] = rand() % n;

		e[j][2] = rand() % 10;
	}

	//sort based on the weights
	for (j = 0; j < edges - 1; j++)
	{
		for (k = j + 1; k < edges; k++)
		{
			if (e[j][3] > e[k][3])
			{
				//swap
				int aux = e[j][3];
				e[j][3] = e[k][3];
				e[k][3] = aux;
			}
		}
	}

	Kruskal(edges, n, e); */

	p.showReport();

	return (0);
}