#include "Glouton.h"

void swap(int ** array, int a, int b){
	int tamponW;
	int tamponV;
	
	tamponW = array[a][0];
	array[a][0] = array[b][0];
	array[b][0] = tamponW;
	
	tamponV = array[a][1];
	array[a][1] = array[b][1];
	array[b][1] = tamponV;
	
}

int ** copyArray(int array[10000][2], int length){
	int ** arrayCopy;
	arrayCopy = malloc(length*sizeof*arrayCopy);
	for(int i=0;i<length;i++){
		arrayCopy[i]=malloc(2*sizeof(int));
		arrayCopy[i][0]=array[i][0];
		arrayCopy[i][1]=array[i][1];
		
		for(int j = i; j > 0; j--)
		{
			double currentRatio = (1.0 *arrayCopy[j][1])/arrayCopy[j][0] ;
			double previousRatio = (1.0 * arrayCopy[j-1][1])/arrayCopy[j-1][0] ;
			
			printf("ratio = %f\n", currentRatio);
			if(currentRatio < previousRatio)
				swap(arrayCopy,i,j);
		}
		
	}
	
	return arrayCopy;
}
