#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
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

void swapValue(Node* node1, Node* node2){
    int mem_temp = node1 -> val;
    node1 -> val = node2 -> val;
    node2 -> val = mem_temp;
}

Heap* openTree(int size) {
    Heap* heap = malloc(sizeof(Heap));
    heap -> size = size;
    heap -> heapArray = malloc(size * sizeof(Node*));
    for(int i = 0; i < size; i++){
       heap -> heapArray[i] = newNode();
    }
   // build parent relation
   for(int j = size - 1; j > 0; j--){
       int p = ceil(j/2) - 1;
       heap -> heapArray[j] -> parent = heap -> heapArray[p];
   }
   // build children relation
   for(int k = 0; k < size; k++){
       int rightNum = 2*(k + 1);
       int leftNum = rightNum - 1;
       if(rightNum < size){
           heap -> heapArray[k] -> rightchild = heap -> heapArray[rightNum];
           heap -> heapArray[k] -> leftchild = heap -> heapArray[leftNum];
           heap -> heapArray[k] -> type = FULL;
       } else if(leftNum < size){
           heap -> heapArray[k] -> leftchild = heap -> heapArray[leftNum];
           heap -> heapArray[k] -> type = SINGLE;
       }
   }
    return heap;
}




void heapify(Node* node, int size){
    int n_val = node -> val;
    if(node -> type == SINGLE) {
        int l_val = node -> leftchild -> val;
        if(n_val > l_val){
            swapValue(node, node -> leftchild);
            heapify(node -> leftchild, size);
        }
    } else if(node -> type == FULL) {
        int l_val = node -> leftchild -> val;
        int r_val = node -> rightchild -> val;
        if(n_val > l_val){
            if(l_val > r_val){
                swapValue(node, node -> rightchild);
                heapify(node -> rightchild, size);
            } else {
                swapValue(node, node -> leftchild);
                heapify(node -> leftchild, size);
            }
        } else {
            if(n_val > r_val){
                swapValue(node, node -> rightchild);
                heapify(node -> rightchild, size);
            }
        }
    }
}




Heap* buildHeap_(int* array, int size){
    Heap* heap = openTree(size);
   for(int i = 0;i < size; i++){
       heap -> heapArray[i] -> val = array[i];
   }
    int j = size;
    while(j > 1){
        int p = floor(j / 2);
        heap -> heapArray[j - 1] -> parent = heap -> heapArray[p - 1];
        j = j - 1;
    }
    return heap;
}


Heap* buildHeap(int* array, int size){
    Heap* heap = buildHeap_(array, size);
    for(int k = floor(size/2); k >= 0; k--){
        heapify(heap -> heapArray[k], heap -> size);
    }
    return heap;
}

Node* extractMin(Heap* heap){
    int last = heap -> size - 1;
    swapValue(heap -> heapArray[0], heap -> heapArray[last]);
    Node* minNode = heap -> heapArray[last];
    // remove pointer from min's parent
    if(minNode -> parent -> type == FULL){
        minNode -> parent -> type = SINGLE;
        minNode -> parent -> rightchild = NULL;
    } else if(minNode -> parent -> type == SINGLE){
        minNode -> parent -> type = NIL;
        minNode -> parent -> leftchild = NULL;
    }

    heap -> heapArray[last] = NULL;
    Node** temp = heap -> heapArray;
    heap -> heapArray = realloc(heap -> heapArray, heap -> size * sizeof(Node*));
    if(heap -> heapArray == NULL){
        heap -> heapArray = temp;
    }
    temp = NULL;
    heap -> size = heap -> size - 1;
    heapify(heap -> heapArray[0], heap -> size);
    return minNode;
}


void freeHeap(Heap* heap){
    int size = heap -> size;
    for(int i = 0; i < size; i++){
        // printf("%x\n", &*(heap -> heapArray + i));
        free(heap -> heapArray[i]);
    }
    free(heap -> heapArray);
    free(heap);
}



// Test heap whether all nodes' values are samller than the values of their children
void verifyHeap(Heap* heap){
    for(int i = 0; i < heap -> size; i++){
        switch (heap -> heapArray[i] -> type) {
            case 2:
                if(heap -> heapArray[i] -> val > heap -> heapArray[i] -> rightchild -> val){
                    printf("[ERROR] Node pointed by heapArray[%d] is bigger than its rightchild.", i);
                    exit(3);
                }
            case 1:
                if(heap -> heapArray[i] -> val > heap -> heapArray[i] -> leftchild -> val){
                    printf("[ERROR] Node pointed by heapArray[%d] is bigger than its leftchild.", i);
                    exit(3);
                }
            case 0:
                break;
        }
    }
}

void verifyNodesType(Heap* heap){
    for(int i = 0; i < heap -> size; i++){
        switch (heap -> heapArray[i] -> type) {
            case 2:
                if(heap -> heapArray[i] -> rightchild == NULL){
                    printf("[ERROR] Node pointed by heapArray[%d] has type of FULL but no rightchild.", i);
                    exit(3);
                }
                if(heap -> heapArray[i] -> leftchild == NULL){
                    printf("[ERROR] Node pointed by heapArray[%d] has type of FULL but no leftchild.", i);
                    exit(3);
                }
                break;
            case 1:
                if(heap -> heapArray[i] -> leftchild == NULL){
                    printf("[ERROR] Node pointed by heapArray[%d] has type of SINGLE but no leftchild.", i);
                    exit(3);
                }
                if(heap -> heapArray[i] -> rightchild != NULL){
                    printf("[ERROR] Node pointed by heapArray[%d] has type of SINGLE but has rightchild.", i);
                    exit(3);
                }
                break;
            case 0:
                if(heap -> heapArray[i] -> leftchild != NULL){
                    printf("[ERROR] Node pointed by heapArray[%d] has type of NULL but has rightchild.", i);
                    exit(3);
                }
                if(heap -> heapArray[i] -> rightchild != NULL){
                    printf("[ERROR] Node pointed by heapArray[%d] has type of SINGLE but has rightchild.", i);
                    exit(3);
                }
                break;
        }
    }
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

void printHeapTree(Heap* heap, char* filePath){
    FILE* outputfile = fopen(filePath, "w");
    outputfile = fopen(filePath, "a");
    int indent = 0;
    printNode(heap -> heapArray[0], outputfile, indent);
    fclose(outputfile);
}

void printHeap(Heap* heap){
    int size = heap -> size;
    for(int i = 0; i < size; i++){
        printf("%d, ", heap -> heapArray[i] -> val);
    }
    printf("\n");
}
