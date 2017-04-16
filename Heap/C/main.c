#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"



void test(){
    int test[10] = {8, 3, 2, 9, 4, 1, 6, 5, 7, 0};
    Heap* testHeap = buildHeap(test, sizeof(test)/4);
    Node* min = extractMin(testHeap);
    free(min);
    verifyHeap(testHeap);
    verifyNodesType(testHeap);
    printHeapTree(testHeap, "./data_output_test.txt");
    printf("The heap should be: 1, 3, 2, 5, 4, 8, 6, 9, 7, \n");
    printf("The heap is:        ");
    printHeap(testHeap);
    freeHeap(testHeap);
}

int main() {
    test();

    return 0;
}