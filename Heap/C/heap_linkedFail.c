#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "heap.h"


// Node in Heap

Node* newNode(){
    Node* node = malloc(sizeof(Node));
    node -> type = NIL;
    node -> val = -1;
    node -> parent = NULL;
    node -> leftchild = NULL;
    node -> rightchild = NULL;
    return node;
}

void swapValue(Node* node){
    int mem_temp = node -> val;
    node -> val = node -> parent -> val;
    node -> parent -> val = mem_temp;
}

void free_nodes_descent(Node* node){
    switch (node -> type) {
        case 2:
            free_nodes_descent(node -> rightchild);
        case 1:
            free_nodes_descent(node -> leftchild);
        case 0:
            free(node);
    }
}


Heap* openHeap() {
    Heap* heap = malloc(sizeof(Heap));
    heap -> last = NULL;
    heap -> root = newNode();
    heap -> size = 1;
    return heap;
}

void freeHeap(Heap* heap){
    free_nodes_descent(heap -> root);
    free(heap);
}

void heapify(Node* node){
    if(node -> parent != NULL){
        int v = node -> val;
        int p = node -> parent -> val;
        if(v < p){
            swapValue(node);
        }
        heapify(node -> parent);
    }
}


Heap* buildTree(int* array, int lengthofArray){
    Heap* heap = openHeap();
    heap -> root -> val = array[0];
    int i = 1;
    heap -> size = lengthofArray;
    Node* pointer = heap -> root;
    Node* pointer_temp = NULL;
    while(i < lengthofArray){
        switch (pointer -> type) {
            case 0:
                pointer -> leftchild = newNode();
                pointer -> type = SINGLE;
                pointer -> leftchild -> parent = pointer;
                pointer -> leftchild -> val = array[i];
                // heap -> size = heap -> size + 1;
                i = i + 1;
                break;
            case 1:
                pointer -> rightchild = newNode();
                pointer -> rightchild -> parent = pointer;
                pointer -> rightchild -> val = array[i];
                pointer -> type = FULL;
                // *(heap -> size) = *(heap -> size) + 1;
                i = i + 1;
                pointer_temp = pointer -> leftchild;
                pointer = pointer_temp;
                pointer_temp = NULL;
                break;
            case 2:
                exit(1);
                break;
        }

    }
    if(pointer -> type == SINGLE){
        heap -> last = pointer -> leftchild;
    } else if(pointer -> type == NIL){
        heap -> last = pointer -> parent -> rightchild;
    } else{
        fprintf(stderr, "pointerError %s:%d:\n", __FILE__, __LINE__);
        exit(2);
    }
    pointer = NULL;
    return heap;
}

// Heap* buildHeap(int* array, int lengthofArray){
//     Heap* heap = buildTree(int* array, int lengthofArray);
//     int count = 0
//     while(count < lengthofArray){
//
//     }
//
// }








void printNode(Node* node, FILE* file, int i){
    int output = -1;
    switch (node -> type) {
        case 2:
            output = node -> val;
            fprintf(file, "%d", output);
            i = i + 1;
            int j = i;
            printNode(node -> leftchild, file, i);
            for(int c = 0; c < i; c++){
                fprintf(file, " ");
            }
            printNode(node -> rightchild, file, j);
            break;
        case 1:
            output = node -> val;
            fprintf(file, "%d", output);
            i = i + 1;
            printNode(node -> leftchild, file, i);
            break;
        case 0:
            output = node -> val;
            fprintf(file, "%d\n", output);


    }
}


void printHeap(Heap* heap, char* filePath){
    FILE* outputfile;
    outputfile = fopen(filePath, "w");
    outputfile = fopen(filePath, "a");
    int indent = 0;
    printNode(heap -> root, outputfile, indent);
    fclose(outputfile);
}














//
