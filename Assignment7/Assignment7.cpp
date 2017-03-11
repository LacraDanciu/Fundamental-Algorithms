/*********************************************************************************************************************************/
/*
Student: Diana Lacramioara Danciu
Group: 30421

A multiway tree is a tree that can have more than two children.
A multiway tree of order m (or an m-way tree) is one in which a tree can have m children.

As with the other trees that have been studied, the nodes in an m-way tree will be made up of key fields,
in this case m-1 key fields, and pointers to children.

To make the processing of m-way trees easier some type of order will be imposed on the keys within each node,
resulting in a multiway search tree of order m ( or an m-way search tree).
By definition an m-way search tree is a m-way tree in which:

 - Each node has m children and m-1 key fields
 - The keys in each node are in ascending order.
 - The keys in the first i children are smaller than the ith key
 - The keys in the last m-i children are larger than the ith key

M-way search trees give the same advantages to m-way trees that binary search trees gave to binary trees
-> they provide fast information retrieval and update.
However, they also have the same problems that binary search trees had - they can become unbalanced,
which means that the construction of the tree becomes of vital importance.

An extension of a multiway search tree of order m is a B-tree of order m. This type of tree will be used
when the data to be accessed/stored is located on secondary storage devices because they allow for
large amounts of data to be stored in a node.

A B-tree of order m is a multiway search tree in which:

The root has at least two subtrees unless it is the only node in the tree.
Each nonroot and each nonleaf node have at most m nonempty children and at least m/2 nonempty children.
The number of keys in each nonroot and each nonleaf node is one less than the number of its nonempty children.
All leaves are on the same level.

These restrictions make B-trees always at least half full, have few levels, and remain perfectly balanced.

The nodes in a B-tree are usually implemented as a class that contains an array of m-l cells for keys,
an array of m pointers to other nodes, and whatever other information is required in order to facilitate tree maintenance.

*********************************************************************************************************************************/

#include<stdlib.h>
#include<conio.h>
#include<stdio.h>

typedef struct node
{
	int key;
	int childNumber;
	struct node **childrenVector;
}TreeM;

typedef struct binaryNode
{
	int key;
	struct binaryNode *firstChild;
	struct binaryNode *brother;
}TreeB;

void insert_Multiway_tree(TreeM **result, int parentVector[], int numberOfElements)
{
	int j;
	TreeM *childNode;
	int childNr;

	childNode = NULL;

	for (j = 1; j <= numberOfElements; j++)
	{
		if (parentVector[j] == result[0]->key)
		{
			childNode = (TreeM*)malloc(sizeof(TreeM));

			if (childNode == NULL)
			{
				printf("MALLOC FAILED!\n");
				exit(1);
			}
			
			childNr = result[0]->childNumber;
			childNode = result[j];
			childNode->key = j;
			result[0]->childrenVector[childNr] = childNode;
			result[0]->childNumber++;
		}
		else
		{
			
			if (parentVector[j] == -1)
			{
				j++;

				childNode = (TreeM*)malloc(sizeof(TreeM));

				if (childNode == NULL)
				{
					printf("MALLOC FAILED!\n");
					exit(1);
				}

				childNr = result[j]->childNumber;
				childNode = result[j];
				childNode->key = j;
				result[parentVector[j]]->childrenVector[childNr] = childNode;
				result[parentVector[j]]->childNumber++;
			}
			else
			{
				childNode = (TreeM*)malloc(sizeof(TreeM));

				if (childNode == NULL)
				{
					printf("MALLOC FAILED!\n");
					exit(1);
				}

				childNr = result[parentVector[j]]->childNumber;
				childNode = result[j];
				childNode->key = j;
				result[parentVector[j]]->childrenVector[childNr] = childNode;
				result[parentVector[j]]->childNumber++;
			}
		}
	}
}

TreeM **create_Multiway_tree(int parentVector[], int numberElements)
{
	TreeM **result;
	int i;
	
	result = NULL;

	result = (TreeM **)malloc((numberElements + 1)*sizeof(TreeM*));

	if (result == NULL)
	{
		printf("MALLOC FAILED!\n");
		exit(1);
	}

	for (i = 1; i <= numberElements; i++)
	{
		result[i] = (TreeM*)malloc(sizeof(TreeM));
		result[i]->childrenVector = (TreeM **)malloc(sizeof(TreeM*)*numberElements);
		result[i]->childNumber = 0;
		printf(" ");
	}
	for (i = 1; i <= numberElements; i++)
	{
		if (parentVector[i] == -1)
		{
			result[0] = (TreeM*)malloc(sizeof(TreeM));
			result[0]->childrenVector = (TreeM **)malloc(sizeof(TreeM*)*(numberElements + 1));
			result[0]->key = i;
			result[0]->childNumber = 0;

		}
		else
		{
			result[parentVector[i]]->key = parentVector[i];
		}
	}

	insert_Multiway_tree(result, parentVector, numberElements);

	return (result);

}

TreeB *createBinaryNode(int key)
{
	TreeB *node;
	node = NULL;
	node = (TreeB *)malloc(sizeof(TreeB));

	if (node == NULL)
	{
		printf("MALLOC FAILED\n");
		exit(1);
	}

	node->firstChild = NULL;
	node->brother = NULL;
	node->key = key;

	return (node);
}

void createBinaryTree(TreeB *rootBinary, TreeM *rootMultiway)
{
	if (rootMultiway != NULL)
	{

		if (rootMultiway->childNumber > 0)
		{
			rootBinary->firstChild = createBinaryNode(rootMultiway->childrenVector[0]->key);
			createBinaryTree(rootBinary->firstChild, rootMultiway->childrenVector[0]);

			rootBinary = rootBinary->firstChild;

			int i = 1;

			while (i < rootMultiway->childNumber)
			{
				rootBinary->brother = createBinaryNode(rootMultiway->childrenVector[i]->key);
				createBinaryTree(rootBinary->brother, rootMultiway->childrenVector[i]);
				rootBinary = rootBinary->brother;
				i++;
			}
			rootBinary->brother = NULL;
		}

		else
		{
			rootBinary->firstChild = NULL;
		}
	}
}

void prettyPrint_Multiway_tree(TreeM *multiWayNode, int level)
{
	int i;

	for (i = 0; i < level; i++)
	{
		printf(" ");
	}

	printf("%d\n", multiWayNode->key);

	for (i = 0; i < multiWayNode->childNumber; i++)
	{
		prettyPrint_Multiway_tree(multiWayNode->childrenVector[i], level + 1);
	}
}

void prettyPrint(TreeB *root, int level) {
	if (root != NULL)
	{
		for (int i = 1; i < 2 * level; i++)
		{
			printf(" ");
		}

		printf("%d\n", root->key);
		prettyPrint(root->firstChild, level + 1);
		prettyPrint(root->brother, level);
	}
}

int main()
{
	TreeB *bRoot;
	TreeM **multiWay;
	int parentVector[] = { 0,2,7,7,3,7,7,-1,5,2 };
	int size = (sizeof(parentVector) / sizeof(parentVector[0])) - 1;

	printf("%d\n", size);
	
	bRoot = NULL;
	bRoot = (TreeB*)malloc(sizeof(TreeB));

	if (bRoot == NULL)
	{
		printf("MALLOC FAILED!\n");
		exit(1);
	}
	
	multiWay = create_Multiway_tree(parentVector, size);

	bRoot->firstChild = NULL;
	bRoot->brother = NULL;
	bRoot->key = multiWay[0]->key;

	createBinaryTree(bRoot, multiWay[0]);
	

	printf("\nMultiway tree representation:\n");
	prettyPrint_Multiway_tree(multiWay[0], 0);
	printf("\nBinary tree representation:\n");
	prettyPrint(bRoot, 0);

	return (0);
}