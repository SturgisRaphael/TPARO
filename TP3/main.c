#include <stdio.h>
#include <stdlib.h>
#include "DecoupeOpti.h"

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

    Decoupe *Instance = malloc(sizeof*Instance);
    initDecoupe(Instance, initWidth, typeNumber, array);
    printDecoupe(Instance);
    freeDecoupe(Instance);

    fclose(file);
}
