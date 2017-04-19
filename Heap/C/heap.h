// Binary MinHeap with array and linked list

#ifndef _heap_h
#define _heap_h

#define NIL 0
#define SINGLE 1
#define FULL 2

typedef struct Node{
    struct Node* parent;
    struct Node* leftchild;
    struct Node* rightchild;
    int val;
    int type;
} Node;

typedef struct Heap{
    int size;
    Node** heapArray;
} Heap;


void freeHeap(Heap* heap);
Heap* buildHeap(int* array, int size);
Node* extractMin(Heap* heap);
void verifyHeap(Heap* heap);
void verifyNodesType(Heap* heap);
void printHeap(Heap* heap);
void printHeapTree(Heap* heap, char* filePath);

#endif