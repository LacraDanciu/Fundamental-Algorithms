/****************************************************************************************************************************************/
/*
	Student: Danciu Diana Lacramioara
	Group: 30421

	Depth first seaech starts from a start node, marked as being in processing (GREY).
	We choose the first unvisited node (WHITE) of this node, we mark it as being in processing(GREY), then for this one we look for the neighbour unvisited and so on.
	When the node doesn't have any unvisited nodes(WHITE), we marked it as processed(BLACK) and we backtrack to the previouse node.
	The algorithm goes on until all the nodes ware processed.
*/

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <vector>
#include "Profiler.h"


using namespace std;
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INFINITE 10000
Profiler p("Depth First Search ");

int verticeees;

typedef struct adjacencyNode
{
	int key;
	vector<adjacencyNode *>destVector;
}adjacencyList;

typedef struct queue_struct
{
	int head, tail, size, capacity;
	adjacencyList **vector;
}Queue;

Queue *create_queue(int capacity)
{
	Queue *queue = (Queue*)malloc(sizeof(Queue));

	queue->capacity = capacity;
	queue->head = queue->size = 0;
	queue->tail = capacity - 1;
	queue->vector = (adjacencyList**)malloc(capacity*sizeof(adjacencyList*));

	return queue;
}

adjacencyList *create_list(int i)
{
	adjacencyList *list = new adjacencyList();

	list->key = i;

	return (list);
}

int isFull(Queue *queue)
{
	return(queue->size == queue->capacity);
}

int isEmpty(Queue *queue)
{
	return(queue->size == 0);
}

void enqueue(Queue *queue, adjacencyList *item)
{
	if (isFull(queue))
	{
		return;
	}
	queue->tail = (queue->tail + 1) % queue->capacity;
	queue->vector[queue->tail] = item;
	queue->size = queue->size + 1;
}

adjacencyList *dequeue(Queue *queue)
{
	if (isEmpty(queue))
	{
		return (NULL);
	}

	adjacencyList* item = queue->vector[queue->head];
	queue->head = (queue->head + 1) % queue->capacity;
	queue->size = queue->size - 1;

	return (item);
}

adjacencyList **create_graph(int V)
{
	adjacencyList **head = new adjacencyList*[V];

	for (int i = 0; i < V; i++)
	{
		head[i] = create_list(i);
	}
	return (head);
}

void add_edge(adjacencyList **graph, int src, int dest)
{
	adjacencyList *list;

	list = graph[dest];
	graph[src]->destVector.push_back(list);
}
void depth_first_search_visit(adjacencyList **graph, int u, adjacencyList *predecessor[], int *color, int *d, int *f, int &time, int &dag, vector<adjacencyList*>&topSort, char total[], int size)
{
	int i;

	color[u] = GRAY;
	time = time + 1;
	d[u] = time;

	p.countOperation(total, size, 1);

	adjacencyList *list = graph[u];

	for (i = 0; i<list->destVector.size(); i++)
	{
		p.countOperation(total, size, 1);
		if (color[list->destVector[i]->key] == WHITE)
		{
			predecessor[i] = list;
			printf("(%d,%d)->Tree edge\n", list->key, list->destVector[i]->key);
			depth_first_search_visit(graph, list->destVector[i]->key, predecessor, color, d, f, time, dag, topSort, total, size);
		}
		else
		{
			if (f[list->destVector[i]->key] == 0)
			{
				printf("(%d,%d)->Back edge\n", list->key, list->destVector[i]->key);
				dag = 1;
			}
			else if (f[list->destVector[i]->key]>d[list->key])
			{
				printf("(%d,%d)->Forward edge\n", list->key, list->destVector[i]->key);
			}
			else
			{
				printf("(%d,%d)->Cross edge\n", list->key, list->destVector[i]->key);
			}

		}
	}
	p.countOperation(total, size, 1);

	color[u] = BLACK;
	time = time + 1;
	f[u] = time;
	topSort.push_back(list);
}

void depth_first_search(adjacencyList **graph, int *color, adjacencyList *predecessor[], int *d, int *f, int V, vector<adjacencyList*> &topSort, int &time, int &dag, char total[], int size)
{
	int u;

	for (u = 0; u < V; u++)
	{
		color[u] = WHITE;
		predecessor[u] = NULL;
	}

	for (u = 0; u < V; u++)
	{
		p.countOperation(total, size, 1);
		if (color[u] == WHITE)
			depth_first_search_visit(graph, u, predecessor, color, d, f, time, dag, topSort, total, size);
	}
}

void add_edges(adjacencyList **graph, int edges)
{
	int k;

	for (k = 1; k <= edges; k++)
	{
		int q = rand() % verticeees;
		int p = rand() % verticeees;

		while (q == p)
		{
			q = rand() % verticeees;
			p = rand() % verticeees;
		}

		add_edge(graph, p, q);
	}

}

void testFixedVertices()
{
	int vertices = 100;
	int time = 0;
	int edges;


	for (edges = 1000; edges <= 4900; edges += 100)
	{
		adjacencyList **graph = create_graph(vertices);

		int *color = (int*)calloc(vertices, sizeof(int));
		int *d = (int*)calloc(vertices, sizeof(int));
		int *f = (int*)calloc(vertices, sizeof(int));

		int dag = 0;

		vector<adjacencyList*> topSort;

		adjacencyList **predecessor = (adjacencyList**)malloc(vertices*sizeof(adjacencyList));
		for (int i = 0; i < vertices; i++)
		{
			predecessor[i] = new adjacencyList();
		}

		verticeees = vertices;
		add_edges(graph, edges);
		depth_first_search(graph, color, predecessor, d, f, vertices, topSort, time, dag, "Total Operations for fixed number of vertices", edges);
	}

}

void testFixedEdges()
{
	int edges = 4950;
	int time = 0;
	int vertices;

	for (vertices = 100; vertices <= 200; vertices += 10)
	{
		adjacencyList **graph = create_graph(vertices);

		int *color = (int*)calloc(vertices, sizeof(int));
		int *d = (int*)calloc(vertices, sizeof(int));
		int *f = (int*)calloc(vertices, sizeof(int));
		int dag = 0;

		vector<adjacencyList*> topSort;

		adjacencyList **predecessor = (adjacencyList**)malloc(vertices*sizeof(adjacencyList));
		for (int i = 0; i < vertices; i++)
			predecessor[i] = new adjacencyList();
		verticeees = vertices;
		add_edges(graph, edges);
		depth_first_search(graph, color, predecessor, d, f, vertices, topSort, time, dag, "Total Operations for fixed number of edges", vertices);

	}
}

void demo()
{
	int V = 6;
	int time = 0;
	int direct_acyclic_graph = 0;
	int i;
	adjacencyList **graph = create_graph(V);

	int *color = (int*)calloc(V, sizeof(int));
	int *d = (int*)calloc(V, sizeof(int));
	int *f = (int*)calloc(V, sizeof(int));

	adjacencyList **predecessor = (adjacencyList**)malloc(V*sizeof(adjacencyList));
	for (i = 0; i < V; i++)
	{
		predecessor[i] = new adjacencyList();
	}

	vector<adjacencyList*> topSort;

	add_edge(graph, 0, 1);
	add_edge(graph, 0, 3);
	add_edge(graph, 1, 2);
	add_edge(graph, 2, 3);
	//addEdge(graph,3,1);
	add_edge(graph, 4, 2);
	add_edge(graph, 4, 5);
	//addEdge(graph,5,5);


	depth_first_search(graph, color, predecessor, d, f, V, topSort, time, direct_acyclic_graph, "Total", 8);

	for (int i = 0; i < V; i++)
	{
		printf("Vertice %d with the adjacent vertices:", graph[i]->key);
		for (int j = 0; j < graph[i]->destVector.size(); j++)
		{
			printf("%d ", graph[i]->destVector[j]->key);
		}
		printf("\n");
	}

	if (direct_acyclic_graph == 1)
	{
		printf("Graph is not topologically sorted");
	}
	else
	{
		printf("The topological order is: ");
		for (int i = 0; i < topSort.size(); i++)
		{
			printf("%d ", topSort[i]->key);
		}
	}
}

int main(int argc, char* argv[])
{
	testFixedEdges();

	//testFixedVertices();

	p.showReport();

	//demo();

	return (0);
}