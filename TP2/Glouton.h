#ifndef GLOUTON_H
#define GLOUTON_H

#include <stdio.h>
#include <stdlib.h>

void swap(int ** array, int a, int b);

int ** copyArray(int array[10000][2], int length);
int glouton(int ** array, int begin,int length, int weightLimit,int weightOffset, int valueOffset);

#endif
