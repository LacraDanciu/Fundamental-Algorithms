/****************************************************************************************************************************************/
/*
Student : Danciu Diana Lacramioara
Group : 30421

Breadth First Search algorithm(BFS) traverses a graph in a breadthwards motion and uses a queue to remember to get the next vertex
to start a search when a dead end occurs in any iteration.

Rules:
Rule 1 − Visit adjacent unvisited vertex. Mark it visited. Display it. Insert it in a queue.

Rule 2 − If no adjacent vertex found, remove the first vertex from queue.

Rule 3 − Repeat Rule 1 and Rule 2 until queue is empty.

Setting/getting a vertex/edge label takes O(1) time
Each vertex is labeled twice once as UNEXPLORED once as VISITED
Each edge is labeled twice once as UNEXPLORED once as DISCOVERY or CROSS
Each vertex is inserted once into a sequence Li
Method incidentEdges is called once for each vertex
BFS runs in O(n + m) time provided the graph is represented by the adjacency list structure
Recall that Σv deg(v) = 2m

->  Time and space complexity
The time complexity can be expressed as O(|V|+|E|), since every vertex and every edge will be explored in the worst case.
|V| is the number of vertices and |E| is the number of edges in the graph. Note that O(|E|) may vary between O(1) and  O(|V|^2),
depending on how sparse the input graph is.
When the number of vertices in the graph is known ahead of time, and additional data structures are used to determine which vertices
have already been added to the queue, the space complexity can be expressed as O(|V|), where |V| is the cardinality of the set of vertices (as said before).
If the graph is represented by an adjacency list it occupies Theta(|V|+|E|) space in memory, while an adjacency matrix representation occupies \Theta(|V|^2).
When working with graphs that are too large to store explicitly (or infinite), it is more practical to describe the complexity of breadth-first search in
different terms: to find the nodes that are at distance d from the start node (measured in number of edge traversals), BFS takes O(bd + 1) time and memory,
where b is the "branching factor" of the graph (the average out-degree).

->  Completeness and optimality
In the analysis of algorithms, the input to breadth-first search is assumed to be a finite graph, represented explicitly as an adjacency list or similar representation.
However, in the application of graph traversal methods in artificial intelligence the input may be an implicit representation of an infinite graph.
In this context, a search method is described as being complete if it is guaranteed to find a goal state if one exists.
Breadth-first search is complete, but depth-first search is not: when applied to infinite graphs represented implicitly,
it may get lost in parts of the graph that have no goal state and never return.

WHITE = 0 means that the vertex wasn't found yet, i.e. wasn't traversed yet. GREY = 1, BLACK =2, they mean that they were discovered.
The diference between GREY and BLACK is that a GREY vertex can have adjacent WHITE vertices, but BLACK has all the adjacent vertices discovered.
We use a queue for the verices that must be processed(discovered) and the list for the adjacent vertices of the graph's each vertex.

We can see that a vertex can be discovered only once, so it can have only one parent.

Complexity of the algorithm is O(M+N) where M = number of vertices and N = number of edges.
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
Profiler profiler("BFS");
int verticeees;

typedef struct adjacencyNode
{
	int key;
	vector<adjacencyNode *> destVector;
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

	return (queue);
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
		return NULL;
	}

	adjacencyList* list = queue->vector[queue->head];

	queue->head = (queue->head + 1) % queue->capacity;
	queue->size = queue->size - 1;

	return (list);
}

adjacencyList **create_graph(int V)
{
	adjacencyList **graph = new adjacencyList*[V];

	for (int i = 0; i < V; i++)
	{
		graph[i] = create_list(i);
	}
	return (graph);
}

void add_edge(adjacencyList **graph, int src, int dest)
{
	adjacencyList *list;

	list = graph[dest];
	graph[src]->destVector.push_back(list);

	list = graph[src];
	graph[dest]->destVector.push_back(list);
}

void breadth_first_search(adjacencyList **graph, int s, int *color, adjacencyList *parent[], int *distance, int V, char total[], int size)
{
	int i;

	//initialize vertices
	for (i = 0; i < V; i++)
	{
		if (i != s)
		{
			color[i] = WHITE;
			distance[i] = INFINITE;
			parent[i] = NULL;
		}
	}

	profiler.countOperation(total, size, 1);

	color[s] = GRAY; // source is grey in the begining of the procedure
	distance[s] = 0;
	parent[s]->key = 0;

	Queue *queue = create_queue(V);

	adjacencyList * source = graph[s];

	profiler.countOperation(total, size, 1);
	enqueue(queue, source); //add s to the queue

	while (isEmpty(queue) == 0) //while still exists grey vertices
	{
		adjacencyList *u = dequeue(queue); //take from the queue what is to be visited

		profiler.countOperation(total, size, 1);
		for (i = 0; i < u->destVector.size(); i++)
		{
			profiler.countOperation(total, size, 1);

			adjacencyList *v = u->destVector[i]; //the list of vertices adjacent to u

			profiler.countOperation(total, size, 1);

			if (color[v->key] == WHITE) //if it's not visited yet
			{
				profiler.countOperation(total, size, 1);

				color[v->key] = GRAY; //vertex becomes grey
				distance[v->key] = distance[u->key] + 1;
				parent[v->key] = u; //we set the parent of this vertex

				profiler.countOperation(total, size, 1);
				enqueue(queue, v); //we add it to the queue
			}
		}
		profiler.countOperation(total, size, 1);

		color[u->key] = BLACK; //when all the vertices adjacent with the vertice that became grey were all examened, it becomes black
	}
}

adjacencyList *transform1(int parents[], int size) {

	adjacencyList *root = NULL;
	adjacencyList **tree = (adjacencyList**)malloc(size * sizeof(adjacencyList*));
	int i;

	for (i = 0; i < size; i++) {
		tree[i] = new adjacencyList();
		tree[i]->key = i;
	}

	for (i = 0; i < size; i++) {

		if (parents[i] != -1) {

			adjacencyList *child = tree[i];

			tree[parents[i]]->destVector.push_back(child);

		}
		else {
			root = tree[i];
		}
	}
	return (root);
}

void prettyPrint(adjacencyList *root, int level)
{
	int i;
	for (i = 0; i < level; i++)
	{
		printf(" ");
	}

	printf("%d\n", root->key);
	for (i = 0; i < root->destVector.size(); i++)
	{
		prettyPrint(root->destVector[i], level + 1);
	}
}

void addEdges(adjacencyList **graph, int edges)
{
	for (double k = 1; k <= edges; k++)
	{
		//generate random vertices of an edge
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

void testFixedVertices(char total[])
{
	int vertices = 100;
	int edges;

	for (edges = 1000; edges <= 4900; edges += 100)
	{
		adjacencyList **graph = create_graph(vertices);

		int *color = (int*)calloc(vertices, sizeof(int));
		int *distance = (int *)calloc(vertices, sizeof(int));

		adjacencyList **parent = new adjacencyList*[vertices];

		for (int i = 0; i < vertices; i++)
		{
			parent[i] = new adjacencyList();
		}

		verticeees = vertices;
		addEdges(graph, edges);
		for (int i = 0; i < vertices; i++)
		{
			profiler.countOperation(total, edges, 1);
			if (color[i] == WHITE)
			{
				breadth_first_search(graph, i, color, parent, distance, vertices, total, edges);
			}
		}
	}
}

void testFixedEdges(char total[])
{
	int edges = 9000;
	int vertices;

	for (vertices = 100; vertices <= 200; vertices += 10)
	{
		adjacencyList **graph = create_graph(vertices);

		int *color = (int*)calloc(vertices, sizeof(int));
		int *distance = (int *)calloc(vertices, sizeof(int));

		adjacencyList **parent = new adjacencyList*[vertices];

		for (int i = 0; i < vertices; i++)
		{
			parent[i] = new adjacencyList();
		}

		verticeees = vertices;
		addEdges(graph, edges);
		for (int i = 0; i < vertices; i++)
		{
			profiler.countOperation(total, vertices, 1);
			if (color[i] == WHITE)
			{
				breadth_first_search(graph, i, color, parent, distance, vertices, total, vertices);
			}
		}
	}
}

void demo()
{
	int V = 8;
	int *color = (int*)calloc(V, sizeof(int));
	int *distance = (int *)calloc(V, sizeof(int));

	adjacencyList **graph = create_graph(V);

	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 3);
	add_edge(graph, 2, 4);
	add_edge(graph, 2, 5);
	add_edge(graph, 4, 5);
	add_edge(graph, 4, 6);
	add_edge(graph, 5, 6);
	add_edge(graph, 5, 7);
	add_edge(graph, 6, 7);

	adjacencyList **parent = new adjacencyList*[V];

	for (int i = 0; i < V; i++)
	{
		parent[i] = new adjacencyList();
	}


	int *parentVector = (int *)calloc(V + 1, sizeof(int));

	breadth_first_search(graph, 0, color, parent, distance, V, "DEMO", V);

	int j = 0;
	for (int i = 0; i < V; i++)
	{
		parentVector[i] = parent[i]->key;
	}

	parentVector[0] = -1;

	adjacencyList *root = transform1(parentVector, V);

	prettyPrint(root, 0);
}

int main(int argc, char* argv[])
{
	//demo();
	testFixedVertices("Total Operations for fixed number of vertices");
	//testFixedEdges("Total Operations for fixed number of edges");

	profiler.showReport();

	return (0);
}