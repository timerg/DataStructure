#ifndef _hash_h
#define _hash_h
#include "linked.h"

typedef struct HashTable{
    Node** table;
    int size;
} HashTable;

HashTable* openTable(int size);
void freeHash(HashTable* hash);

// direct address search
Node* DASearch(HashTable* hash, int k);

// direct address insert
void DAInsert(HashTable* hash, int k);

// direct address delete
void DADelte(HashTable* hash, int k);


#endif