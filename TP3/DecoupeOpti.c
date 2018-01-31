#include "DecoupeOpti.h"

void initDecoupe(Decoupe *this,int initWidth, int typeNumber, int array[10000][2]){
    this->initWidth = initWidth;
    this->typeNumber = typeNumber;

    this->initialMatrix = malloc(typeNumber*sizeof*this->initialMatrix);
    for(int i=0; i<typeNumber; i++){
        this->initialMatrix[i] = malloc(2*sizeof(int));

        this->initialMatrix[i][0] = array[i][0];
        this->initialMatrix[i][1] = array[i][1];
    }

}

void freeDecoupe(Decoupe *this){
    for(int i=0;i<this->typeNumber;i++){
        free(this->initialMatrix[i]);
    }
    free(this->initialMatrix);
    free(this);

}

void printDecoupe(Decoupe *this){
    printf("largeur max : %d \n",this->initWidth);
	printf("nombre de tailles de coupes : %d \n",this->typeNumber);
    printf("\n");
	for(int i =0;i<this->typeNumber;i++){
		printf("%d rouleaux de largeur %d \n",this->initialMatrix[i][0],this->initialMatrix[i][1] );

	}

}
