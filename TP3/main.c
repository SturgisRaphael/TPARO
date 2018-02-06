#include <stdio.h>
#include <stdlib.h>
#include "order.h"

int main(int argc, char* argv[])
{
    if(argc!=2){
		printf("Pas le bon nombre d'arguments\n");
		exit(1);
	}

	FILE* file = fopen(argv[1],"r");
	int initWidth;
	fscanf(file,"%d",&initWidth);

	int typeNumber = 0;
	int array[10000][2];

	while(fscanf(file,"%d %d",&array[typeNumber][0], &array[typeNumber][1]) ==2){
		typeNumber++;
	}

    order *Instance = malloc(sizeof*Instance);
    initOrder(Instance, initWidth, typeNumber, array);
    printOrder(Instance);
    freeOrder(Instance);

    fclose(file);
}
