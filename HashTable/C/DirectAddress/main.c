#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int main() {
    HashTable* hash = openTable(1000);
    DAInsert(hash, 3);
    Node* n = DASearch(hash, 3);
    DADelte(hash, 3);
    n = NULL;
    freeHash(hash);
    return 0;

}


