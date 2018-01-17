#ifndef ARBRE_H
#define ARBRE_H

typedef struct node *tree;

typedef struct node
{
	int weight;
	int value;
	
	int cumulatedWeight;
	int cumulatedValue;
	
	int index;
	
	tree left, right, parent;
}node;

#endif
