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
		
		if(i>0){
		
			double currentRatio = (1.0 *arrayCopy[i][1])/arrayCopy[i][0] ;
			double previousRatio = (1.0 * arrayCopy[i-1][1])/arrayCopy[i-1][0] ;
			int j = i;
			
			while(currentRatio > previousRatio && j > 0){
				swap(arrayCopy,j,j-1);
				j--;
				
				if(j>0){
					currentRatio = (1.0 *arrayCopy[j][1])/arrayCopy[j][0] ;
					previousRatio = (1.0 * arrayCopy[j-1][1])/arrayCopy[j-1][0] ;
				}
			}	
		}
		
	}
	
	return arrayCopy;
}

int glouton(int ** array, int begin,int length, int weightLimit,int weightOffset, int valueOffset)
{
	int capacity = weightLimit - weightOffset;
	int value = valueOffset;
	
	if(weightOffset > weightLimit)
	{
		printf("Error: weightOffset > weightLimit\n");
		exit(1);
	}
	
	if(begin > length)
	{
		printf("Error: begin > length\n");
		exit(1);
	}
	
	for(int i = begin; i < length; i++)
	{
		if(array[i][0] > capacity)
		{
			value += (array[i][1] * capacity) / array[i][0];
			break;
		}
		
		value += array[i][1];
		capacity -= array[i][0];
	}
	
	return value;
}
