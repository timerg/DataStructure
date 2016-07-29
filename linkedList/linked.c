#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

// data List = Nil              -- type = NIL
//           | Cons Int List    -- type = CONS






// smart constructor
Node* new() {
    Node* node = malloc(sizeof(Node));
    node -> type = NIL;
    return node;
    
}

Node* cons(int val, Node* xs) {
    Node* node = malloc(sizeof(Node));
    node -> type = CONS;
    node -> val = val;
    node -> next = xs;
    return node;
}

int length(Node* node) {
    if(node -> type == NIL){
        return 0;
    } else {
        return (1 + length(node -> next));
    }
}

Node* insert_at(int x, unsigned int n, Node *node) {
    if (node -> type == NIL) {
        printf("error: index is too long for insert\n");
        return node;
    } else {
        if (n == 0) {
            return (cons(x, node));
        } else {
            node -> next = insert_at(x, (n - 1), node -> next);
            return node;
        }
    }
}

void free_list(Node* xs) {
    if (xs -> type == NIL) {
        // Nil
        free(xs);
    } else {
        // Cons
        free_list(xs -> next);
        free(xs);
    }
}

int sum(Node* xs) {
    if(xs -> type ==NIL) {
        return 0;
    } else {
        return ((xs -> val) + sum(xs -> next));
    }
}
void print_list(Node* xs) {
    if (xs -> type == NIL) {
        // Nil
        printf("[]\n");
    } else {
        // Cons
        printf("%d ", xs -> val);
        print_list(xs -> next);
    }
}
