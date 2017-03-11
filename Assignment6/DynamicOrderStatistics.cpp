#include<iostream>
#include<conio.h>
#include "Profiler.h"

/**********************************************************************************************************************************

# Student: Danciu Diana Lacramioara
# Group: 30421

In computer science, an order statistic tree is a variant of the binary search tree
(or more generally, a B-tree[1]) that supports two additional operations beyond insertion, lookup and deletion:

Select(i) — find the i'th smallest element stored in the tree
Rank(x) – find the rank of element x in the tree, i.e. its index in the sorted list of elements of the tree

Both operations can be performed in O(log n) time in the average case; when a self-balancing tree is used as the base data structure,
this bound also applies in the worst case.

*/

Profiler profiler("DynamicOrderStatistics");

#define MAXSIZE 10000

typedef struct node
{
	struct node *left;
	struct node *right;
	struct node *parent;
	int value;
	int size;
} TreeT;

int n;
TreeT *root;

TreeT * createNode(int value)
{
	TreeT *aTree = (TreeT*)malloc(sizeof(TreeT));
	if (aTree)
	{
		aTree->value = value;
		aTree->size = 0;
		aTree->left = NULL;
		aTree->right = NULL;
		aTree->parent = NULL;
	}
	return (aTree);
}

TreeT* find_minimum_tree(TreeT *x)
{
	profiler.countOperation("Dynamic operations", n, 1);
	while (x->left->value != -1)
	{
		profiler.countOperation("Dynamic operations", n, 3);
		x->size--;
		x = x->left;
	}
	return (x);
}
TreeT *tree_successor(TreeT *tree)
{
	TreeT *y = createNode(-1);

	profiler.countOperation("Dynamic operations", n, 1);
	if (tree->right->value != -1)
	{
		return (find_minimum_tree(tree->right));
	}
	y = tree->parent;

	while ((y->value != -1) && (tree == y->right))
	{
		tree = y;
		y = y->parent;
	}

	return (y);
}

TreeT* OS_Delete(TreeT *z)
{
	TreeT *y = createNode(-1);
	TreeT *x = createNode(-1);

	profiler.countOperation("Dynamic operations", n, 2);
	if ((z->left->value == -1) || (z->right->value == -1))
	{
		y = z;
	}
	else
	{
		y = tree_successor(z);
	}

	profiler.countOperation("Dynamic operations", n, 2);
	if (y->left->value != -1)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}

	profiler.countOperation("Dynamic operations", n, 1);
	if (x->value != -1)
	{
		x->parent = y->parent;
		profiler.countOperation("Dynamic operations", n, 1);
	}

	profiler.countOperation("Dynamic operations", n, 1);
	if (y->parent == NULL)
	{
		profiler.countOperation("Dynamic operations", n, 1);
		root = x;
	}
	else
	{
		profiler.countOperation("Dynamic operations", n, 2);
		if (y == y->parent->left)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}
	}

	profiler.countOperation("Dynamic operations", n, 1);
	if (y != z)
	{
		z->value = y->value;
		profiler.countOperation("Dynamic operations", n, 1);
	}
	return (y);

}

TreeT * OS_Select(TreeT *x, int rank)
{
	int r;
	r = x->left->size + 1;
	profiler.countOperation("Dynamic operations", n, 1);
	profiler.countOperation("Dynamic operations", n, 1);
	if (r == rank)
	{
		x->size--;

		return (x);
	}
	else
	{
		profiler.countOperation("Dynamic operations", n, 2);
		if (rank < r)
		{
			x->size--;

			return (OS_Select(x->left, rank));
		}
		else
		{
			x->size--;
			return (OS_Select(x->right, rank - r));
		}
	}
}


TreeT *insert(int l, int r, int arr[])
{
	TreeT *newNode = createNode(-1);

	if (l < r)
	{
		newNode->value = arr[(l + r) / 2];
		newNode->size = r - l;

		newNode->left = insert(l, (l + r) / 2, arr);
		newNode->left->parent = newNode;

		newNode->right = insert((l + r) / 2 + 1, r, arr);
		newNode->right->parent = newNode;
	}
	return (newNode);
}

void prettyPrint(TreeT* root, int depth)
{
	int i;

	if (root != NULL)
	{
		prettyPrint(root->right, depth + 1);

		for (i = 0; i < depth; i++)
		{
			printf("	");
		}

		if (root->value != -1)
		{
			printf("%d (%d) ", root->value, root->size);
		}


		printf("\n");
		prettyPrint(root->left, depth + 1);
	}
}

TreeT* createTree(int n1)
{
	int arr[MAXSIZE];
	for (int i = 0; i < n1; i++)
	{
		arr[i] = i + 1;
	}

	TreeT *node = createNode(-1);
	node = insert(0, n1, arr);

	prettyPrint(node, 0);
	return (node);

}

int main()
{
	int i, rank;
	TreeT *my_tree;
	my_tree = NULL;

	for (i = 0; i < 5; i++)
	{
		for (n = 100; n <= MAXSIZE; n += 100)
		{
			root = createTree(n);
			for (int l = n; l > 0; l--)
			{
				rank = rand() % l + 1;
				my_tree = OS_Select(root, rank);
				OS_Delete(my_tree);
			}
		}
	}
	profiler.createGroup("Dynamic overall operations", "Dynamic operations");
	profiler.showReport();
	return (0);
}