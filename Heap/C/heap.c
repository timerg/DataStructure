#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


// Node in Heap

Node* newNode(){
    Node* node = malloc(sizeof(Node));
    node -> type = NIL;
    node -> val = -1;
    node -> leftchild = NULL;
    node -> rightchild = NULL;
    return node;
}

void free_nodes(Node* node){
    switch (node -> type) {
        case 2:
            free_nodes(node -> rightchild);
        case 1:
            free_nodes(node -> leftchild);
        case 0:
            free(node);
    }
}


Heap* buildHeap() {
    Heap* heap = malloc(sizeof(Heap));
    heap -> root = newNode();
    heap -> size = 1;
    return heap;
}

void freeHeap(Heap* heap){
    free_nodes(heap -> root);
    free(heap);
}


Heap* arrayToTree(int* array, int lengthofArray){
    Heap* heap = buildHeap();
    heap -> root -> val = array[0];
    int i = 1;
    Node* pointer = heap -> root;
    Node* pointer_temp = NULL;
    while(i < lengthofArray){
        switch (pointer -> type) {
            case 0:
                pointer -> leftchild = newNode();
                pointer -> type = SINGLE;
                pointer -> leftchild -> val = array[i];
                // heap -> size = heap -> size + 1;
                i = i + 1;
                break;
            case 1:
                pointer -> rightchild = newNode();
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
    pointer = NULL;
    return heap;
}










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
