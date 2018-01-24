#include <stdio.h>
#include <stdlib.h>
#include "Arbre.h"
#include "Glouton.h"

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Pas le bon nombre d'arguments\n");
		exit(1);
	}
	
	FILE* file = fopen(argv[1],"r");
	int maxWeight = 0;
	fscanf(file,"%d",&maxWeight);
	
	int index = 0;
	int array[10000][2];
	
	while(fscanf(file,"%d %d",&array[index][0], &array[index][1]) ==2){
		index++;
	}
	
	printf("poid max : %d \n",maxWeight);
	printf("nombre d'objets : %d \n",index);
	for(int i =0;i<index;i++){
		printf("objet %d, poid %d, valeur %d \n",i,array[i][0],array[i][1] );
	
	}
	
	int ** sortedArray = copyArray(array, index);
	for(int i =0;i<index;i++){
		printf("objet %d, poid %d, valeur %d, ratio = %f\n",i,sortedArray[i][0],sortedArray[i][1], (1.0*sortedArray[i][1])/sortedArray[i][0]);
	
	}
	
	//printf("Glouton 15-15:\t%d\nGlouton 14-15\t%d\nGlouton 0-15\t%d\n", glouton(sortedArray, 15, 15, 1000, 0, 0), glouton(sortedArray, 14, 15, 1000, 0, 0), glouton(sortedArray, 0, 15, 1000, 0, 0));
	
	tree t = initTree();
	t->index = 0;
	t->cumulatedWeight = 0;
	t->cumulatedValue = 0;
	t->optimalValue = 0;
	knapsack(sortedArray, maxWeight, index, t);
	
	
	printf("Knapsack optimalValue = %d\n", t->optimalValue);
	
	for(int i =0;i<index;i++){
		free(sortedArray[i]);
	}
	
	freeTree(t);
	
	
	free(sortedArray);
	
	fclose(file);
}
