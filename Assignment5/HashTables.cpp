#include<iostream>
#include<conio.h>
#include "Profiler.h"

/********************************************************************************************************************************************************* /

 *Student: Danciu Diana Lacramioara 
 *Group: 30421

A chained hash table indexes into an array of pointers to the heads of linked lists.
Each linked list cell has the key for which it was allocated and the value which was inserted for that key.
When you want to look up a particular element from its key, the key's hash is used to work out which linked list to follow,
and then that particular list is traversed to find the element that you're after. If more than one key in the hash table has the same hash,
then you'll have linked lists with more than one element.

The downside of chained hashing is having to follow pointers in order to search linked lists.
The upside is that chained hash tables only get linearly slower as the load factor
(the ratio of elements in the hash table to the length of the bucket array) increases, even if it rises above 1.

An open-addressing hash table indexes into an array of pointers to pairs of (key, value).
You use the key's hash value to work out which slot in the array to look at first.
If more than one key in the hash table has the same hash, then you use some scheme to decide on another slot to look in instead.
For example, linear probing is where you look at the next slot after the one chosen, and then the next slot after that,
and so on until you either find a slot that matches the key you're looking for, or you hit an empty slot (in which case the key must not be there).

Open-addressing is usually faster than chained hashing when the load factor is low because you don't have to follow pointers between list nodes.
It gets very, very slow if the load factor approaches 1, because you end up usually having to search through many of the slots in the bucket array
before you find either the key that you were looking for or an empty slot.
Also, you can never have more elements in the hash table than there are entries in the bucket array.

To deal with the fact that all hash tables at least get slower (and in some cases actually break completely)
when their load factor approaches 1, practical hash table implementations make the bucket array larger
(by allocating a new bucket array, and copying elements from the old one into the new one, then freeing the old one)
when the load factor gets above a certain value (typically about 0.7).


Hash tables are O(1) average and amortized case complexity, however it suffers from O(n) worst case time complexity.

Hash tables suffer from O(n) worst time complexity due to two reasons:

If too many elements were hashed into the same key: looking inside this key may take O(n) time.
Once a hash table has passed its load balance - it has to rehash [create a new bigger table, and re-insert each element to the table].
However, it is said to be O(1) average and amortized case because:
	it is very rare that many items will be hashed to the same key (if we chose a good hash function and we don't have too big load balance).
	The rehash operation, which is O(n), can at most happen after n/2 ops, which are all assumed O(1).
	Thus when we sum the average time per operation, we get : (n*O(1) + O(n)) / n) = O(1)

Another issue where we might see a performance loss in large hash tables is due to cache performance.
Hash Tables suffer from bad cache performance, and thus for large collection - the access time might take longer,
since we need to reload the relevant part of the table from the memory back into the cache.
*/

Profiler p("HashTables");

#define SIZE 10007
#define searchSize 1500

int linearHashFunction(int key, int i, int m)
{
	return ((key + i) % m);
}

int quadraticHashFunction(int key, int i, int m)
{
	return ((key + (5 * i) + 3 * i*i) % m);
}

int linearHashSearch(int *hashTable, int key, int m, int &countFound, int &countNotFound, int &maxFound, int &maxNotFound)
{
	int i = 0, j;
	do
	{
		j = linearHashFunction(key, i, m);
		p.countOperation("HASH", m, 1);
		if (hashTable[j] == key)
		{
			countFound += (i + 1);
			if ((i + 1) > maxFound)
			{
				maxFound = (i + 1);
			}
			return (j);
		}
		i++;
		p.countOperation("HASH", m, 1);
	} while ((hashTable[j] != 0) && (i != m));

	countNotFound += (i + 1);
	if ((i + 1) > maxNotFound)
	{
		maxNotFound = i + 1;
	}

	return (-1);

}

int linearHashInsert(int *hashTable, int key, int m)
{
	int i = 0, j, a, b, c, d;

	while (i < m)
	{
		if (linearHashSearch(hashTable, key, m, a, b, c, d) != -1)
		{
			return (-1);
		}

		j = linearHashFunction(key, i, m);
		if (hashTable[j] == 0)
		{
			hashTable[j] = key;
			return (j);
		}
		i++;
	}
	return (0);
}

int quadraticHashSearch(int *hashTable, int key, int m, int &countFound, int &countNotFound, int &maxFound, int &maxNotFound)
{
	int i = 0, j;
	do
	{
		j = quadraticHashFunction(key, i, m);
		p.countOperation("HASH2", m, 1);
		if (hashTable[j] == key)
		{
			countFound += (i + 1);
			if ((i + 1) > maxFound)
			{
				maxFound = i + 1;
			}
			return (j);
		}
		i++;
		p.countOperation("HASH2", m, 1);
	} while ((hashTable[j] != 0) && (i < m));

	countNotFound += (i + 1);
	if ((i + 1) > maxNotFound)
	{
		maxNotFound = i + 1;
	}

	return (-1);
}

int quadraticHashInsert(int *hashTable, int key, int m)
{
	int i = 0, j, a, b, c, d;

	while (i < m)
	{
		if (quadraticHashSearch(hashTable, key, m, a, b, c, d) != -1)
		{
			return (-1);
		}

		j = quadraticHashFunction(key, i, m);
		if (hashTable[j] == 0)
		{
			hashTable[j] = key;
			return (j);
		}
		i++;
	}
	return (0);
}

int main()
{
	FILE *file;
	int hashInsertDemo[10] = { 9,8,2,3,4,5,7,6,1,10 };
	int a, b, c, d, size, k, min, i, j, p, maxFoundTotal, maxNotFoundTotal, newSize, countFound, countNotFound, maxFound;
	int maxNotFound, random;
	int *hashT, *temp, *notFound, *found;
	double fill[5] = { 0.8,0.85,0.9,0.95,0.99 };
	int hash[10];
	double avgEffortFound, avgEffortNotFound, avgEffortFoundTotal, avgEffortNotFoundTotal;

	k = 0;
	min = 0;

	fopen_s(&file, "file.txt", "a");

	fprintf(file, "The filling factor |  Avg effort found |  Max effort found  | Avg effort Not Found  | Max effort not found \n");

	for (i = 0; i < 10; i++)
	{
		hash[i] = 0;
	}
	size = sizeof(hash) / sizeof(hash[0]);

	for (j = 0; j < 10; j++)
	{
		quadraticHashInsert(hash, hashInsertDemo[j], size);
	}

	for (i = 0; i < 10; i++)
	{
		printf("%d ", hash[i]);
	}
	for (i = 0; i < 10; i++)
	{
		if (quadraticHashSearch(hash, hashInsertDemo[i], size, a, b, c, d) != -1)
		{
			printf("found! ");
		}
	}

	for (p = 0; p < 5; p++)
	{
		avgEffortFoundTotal = 0;
		avgEffortNotFoundTotal = 0;
		maxFoundTotal = 0;
		maxNotFoundTotal = 0;
		newSize = SIZE*fill[p];

		for (j = 0; j < 5; j++)
		{
			k = 0;
			hashT = (int*)calloc(SIZE + 1, sizeof(int));
			temp = (int *)calloc(newSize + 1, sizeof(int));
			found = (int *)calloc(newSize + 1, sizeof(int));
			notFound = (int *)calloc(searchSize + 1, sizeof(int));
			avgEffortFound = 0;
			avgEffortNotFound = 0;
			countFound = 0;
			countNotFound = 0;
			maxFound = -1;
			maxNotFound = -1;

			FillRandomArray(temp, newSize, 10, 50000, true, 0);
			for (i = 0; i < newSize; i++)
			{
				if (quadraticHashInsert(hashT, temp[i], SIZE) != -1)
				{
					found[k++] = temp[i];
				}
			}

			for (i = 0; i < 1500; i++)
			{
				random = rand() % k;
				quadraticHashSearch(hashT, found[random], SIZE, countFound, countNotFound, maxFound, maxNotFound);
			}


			FillRandomArray(notFound, 1500, 50001, 100000, true, 0);

			for (i = 0; i < 1500; i++)
			{
				quadraticHashSearch(hashT, notFound[i], SIZE, countFound, countNotFound, maxFound, maxNotFound);
			}

			avgEffortFound = (double)countFound / 1500.0;
			avgEffortNotFound = (double)countNotFound / 1500.0;

			avgEffortFoundTotal += avgEffortFound;
			avgEffortNotFoundTotal += avgEffortNotFound;
			maxFoundTotal += maxFound;
			maxNotFoundTotal += maxNotFound;

			for (i = 0; i < SIZE; i++)
			{
				hashT[i] = 0;
			}

		}

		avgEffortFoundTotal = avgEffortFoundTotal / 5.0;
		avgEffortNotFoundTotal = avgEffortNotFoundTotal / 5.0;
		maxFoundTotal = maxFoundTotal / 5.0;
		maxNotFoundTotal = maxNotFoundTotal / 5.0;

		fprintf(file, "       %f           %f           %d                       %.2f                  %d\n", fill[p], avgEffortFoundTotal, maxFoundTotal, avgEffortNotFoundTotal, maxNotFoundTotal);
	}

	fclose(file);
	return (0);
}