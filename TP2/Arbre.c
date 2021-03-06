#include "Arbre.h"

extern int count;

tree initTree()
{
	tree t = malloc(sizeof(node));
	
	t->left = NULL;
	t->right = NULL;
	t->parent = NULL;
	return t;
}

int maxOptiValue(tree left, tree right)
{
	if(right == NULL && left == NULL)
		return 0;
	else if(right == NULL)
		return left->optimalValue;
	else if(left == NULL)
		return right->optimalValue;
	else
		return max(left->optimalValue, right->optimalValue);
	
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void knapsack(int ** array, int capacity, int length, tree t)
{
	count++;
	int index = t->index;
	
	
	if(index >= length)
	{
		if(t->cumulatedValue > t->optimalValue)
			t->optimalValue = t->cumulatedValue;
		else
			t->optimalValue = -1;
		return;
	}
	
	if(glouton(array, index, length, capacity + t->cumulatedWeight, t->cumulatedWeight, t->cumulatedValue) < t->optimalValue){
		t->optimalValue = -1;
		return;
	}

	if(array[index][0] <= capacity)
	{
		//printf("right\n");
		t->right = initTree();
		t->right->cumulatedValue = t->cumulatedValue + array[index][1];
		t->right->cumulatedWeight = t->cumulatedWeight + array[index][0];
		t->right->index = index + 1;
		t->right->parent = t;
		t->right->optimalValue = t->optimalValue;
		knapsack(array, capacity - array[index][0], length, t->right);
		t->optimalValue = maxOptiValue(t->left, t->right);
	}
	//printf("left\n");
	t->left = initTree();
	t->left->cumulatedValue = t->cumulatedValue;
	t->left->cumulatedWeight = t->cumulatedWeight;
	t->left->index = index + 1;
	t->left->parent = t;
	t->left->optimalValue = t->optimalValue;
	knapsack(array, capacity, length, t->left);
	
	t->optimalValue = maxOptiValue(t->left, t->right);
}

void freeTree(tree t)
{
	if(t->left != NULL)
		freeTree(t->left);
	if(t->right != NULL)
		freeTree(t->right);
	free(t);
}
