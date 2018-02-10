#ifndef H_ORDER
#define H_ORDER

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ** array;
    int initWidth;
    int numberSizes;

} order;

void initOrder(order *this,int initWidth, int numberSizes, int array[10000][2]);

void freeOrder(order *this);

void printOrder(order *this);

#endif