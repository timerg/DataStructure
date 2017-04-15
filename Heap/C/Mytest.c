#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include "dbg.h"
#include "heap.h"




void testA(){
    int test[5] = {1, 2, 3, 4, 5};
    Heap* testHeap = buildTree(test, sizeof(test)/4);
    assert(testHeap -> root != NULL);
    assert(testHeap -> root -> val == 1);
    assert(testHeap -> root -> leftchild != NULL);
    assert(testHeap -> root -> leftchild -> val == 2);
    assert(testHeap -> root -> leftchild -> type == FULL);
    assert(testHeap -> root -> rightchild != NULL);
    assert(testHeap -> root -> rightchild -> val == 3);
    assert(testHeap -> root -> rightchild -> leftchild == NULL);
    assert(testHeap -> root -> leftchild -> leftchild != NULL);
    assert(testHeap -> root -> leftchild -> leftchild -> val = 4);
    assert(testHeap -> root -> leftchild -> leftchild -> leftchild == NULL);
    assert(testHeap -> root -> leftchild -> rightchild -> val = 5);
    assert(testHeap -> size = sizeof(test)/4)
    printHeap(testHeap, "./data_output_test.txt");
    freeHeap(testHeap);
}

void testB(){
    int test[10] = {8, 3, 2, 9, 4, 1, 6, 5, 7, 0};
    Heap* testHeap = buildTree(test, sizeof(test)/4);
    heapify(testHeap -> last);
    assert(testHeap -> root -> val == test[9]);
}


int main() {
    // testA();
    testB();
    return 0;
}