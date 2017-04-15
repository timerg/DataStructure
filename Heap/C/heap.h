// Binary MinHeap with linked list
// Use recursion to implement linled list

#ifndef _heap_h
#define _heap_h

#define NIL 0
#define SINGLE 1
#define FULL 2

typedef struct Node{
    struct Node* leftchild;
    struct Node* rightchild;
    int val;
    int type;
} Node;

typedef struct Heap{
    Node* root;
    int size;
} Heap;

Node* newNode();
void free_nodes(Node* node);

Heap* buildHeap();
void freeHeap(Heap* heap);
Heap* arrayToTree(int* array, int lengthofArray);
void heapify(Node* node);
Node* extractMin(Heap* heap);
void printNode(Node* node, FILE* file, int i);
void printHeap(Heap* heap, char* filePath);


#endif