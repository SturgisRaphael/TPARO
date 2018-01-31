#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ** initialMatrix;
    int initWidth;
    int typeNumber;

} Decoupe;

void initDecoupe(Decoupe *this,int initWidth, int typeNumber, int array[10000][2]);

void freeDecoupe(Decoupe *this);

void printDecoupe(Decoupe *this);
