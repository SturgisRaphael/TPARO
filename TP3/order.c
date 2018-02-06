#include "order.h"

void initOrder(order *this,int initWidth, int typeNumber, int array[10000][2]){
    this->initWidth = initWidth;
    this->numberSizes = typeNumber;

    this->array = malloc(typeNumber*sizeof*this->array);
    for(int i=0; i<typeNumber; i++){
        this->array[i] = malloc(2*sizeof(int));

        this->array[i][0] = array[i][0];
        this->array[i][1] = array[i][1];
    }

}

void freeOrder(order *this){
    for(int i=0;i<this->numberSizes;i++){
        free(this->array[i]);
    }
    free(this->array);
    free(this);

}

void printOrder(order *this){
    printf("max width : %d \n",this->initWidth);
	printf("sizes : %d \n",this->numberSizes);
    printf("\n");
	for(int i =0;i<this->numberSizes;i++){
		printf("%d rouleaux de largeur %d \n",this->array[i][0],this->array[i][1] );

	}

}
