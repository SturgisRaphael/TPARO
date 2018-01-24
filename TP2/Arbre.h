#ifndef ARBRE_H
#define ARBRE_H

#include <stdlib.h>
#include "Glouton.h"

typedef struct node *tree;

typedef struct node
{
	int cumulatedWeight;
	int cumulatedValue;
	
	int optimalValue;
	
	int index;
	
	tree left, right, parent;
}node;

tree initTree();
int maxOptiValue(tree left, tree right);
int max(int a, int b);
void knapsack(int ** array, int capacity, int length, tree t);
void freeTree(tree t);

#endif
