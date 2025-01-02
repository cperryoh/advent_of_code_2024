#include <stdio.h>
#include "utils.h"
void printArray(int A[], int size) {
    int i;
    printf("[");
    for (i = 0; i < size; i++){
      printf("%d", A[i]);
      if(i < size-1)
        printf(", ");
      else
        printf("]");
    }
    printf("\n");
}
