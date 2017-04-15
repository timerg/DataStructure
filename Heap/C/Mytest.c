#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include "dbg.h"
#include "heap.h"




void testA(){
    int test[5] = {1, 2, 3, 4, 5};
    Heap* testHeap = arrayToTree(test, sizeof(test)/4);
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
    printHeap(testHeap, "./data_output.txt");
    freeHeap(testHeap);
}


int main() {
    testA();
    typedef struct N{
        int* a;
        int b;
    } N;
    N* n1 = malloc(sizeof(N));
    n1 -> b = 1;
    // printf("%d\n", *n1 -> a == NULL);
    free(n1);
    // a = a_temp;
    // a_temp = NULL;
    // printf("a=%d, b=%d\n", *a, *b);
    return 0;
}