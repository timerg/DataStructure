#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "linked.h"

HashTable* openTable(int size){
    HashTable* hash = malloc(sizeof(HashTable));
    hash -> table = malloc(size *  sizeof(Node*));
    for(int i = 0; i < size; i++){
        hash -> table[i] = newNode();
    }
    hash -> size = size;
    return hash;
}

void freeHash(HashTable* hash){
    for(int i = 0; i < hash -> size; i++){
        free_list(hash -> table[i]);
    }
    free(hash -> table);
    free(hash);
}

Node* DASearch(HashTable* hash, int k){
    return hash -> table[k];
}

void DAInsert(HashTable* hash, int k){
    hash -> table[k] -> val = k;
    hash -> table[k] -> type = CONS;
    hash -> table[k] -> next = newNode();
}

void DADelte(HashTable* hash, int k){
    free_list(hash -> table[k]);
    hash -> table[k] = newNode();

}