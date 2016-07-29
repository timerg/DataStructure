#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
// Remove from "front"; Insert from "rear"





void free_Node(Node *n){
    if(n -> type == NIL) {
        free(n);
    } else {
            free_Node(n -> next);
            free(n);
        }
}

Node* nil() {
    Node* node = malloc(sizeof(Node));
    node -> type = NIL;
    return node;
}

void print_list(Node *n) {
    if (n -> type == NIL) {
        printf("[]\n");
    } else {
        // Cons
        printf("%d ", n -> val);
        print_list(n -> next);
    }
}

int length_node(Node *n){
    if(n -> type != NIL){
        return (1 + length_node(n -> next));
    }
    else
        return 0;
}
/*-------    Queue   ----------*/


Que* new_Queue() {
    Que *q = malloc(sizeof(Que));
    q -> list = nil();
    q -> rear = q -> list;
    return q;
}

void free_list(Que *q){
    free_Node(q -> list);
    free(q);
}

int is_empty(Que *q){
    if(q -> list == q -> rear) return 1;
        else return 0;
}

// ([], _) ([r], r_new)

Que *enque(int val, Que *q) {
    if(is_empty(q) == 1){
        q -> list = malloc(sizeof(Node));
        q -> list -> val = val;
        q -> list -> type = CONS;
        q -> list -> next = q -> rear;
        return q;
    } else {
        Node* node_new = malloc(sizeof(Node));
        node_new -> type = NIL;
        q -> rear -> next = node_new;
        q -> rear -> val = val;
        q -> rear -> type = CONS;
        q -> rear = q -> rear -> next;
        return q;
    }
}

Que *deque(Que *q) {
    if(is_empty(q) == 1){
        return q;
    } else {
        Node *temp = q -> list;
        q -> list = q -> list -> next;
        free(temp);
        return q;
    }
}

int pop(Que *q) {
    if(is_empty(q) == 1){
        printf("It's empty\n");
        exit(1);
    } else {
        return (q -> list -> val);
    }
}

void print_Queue(Que *q){
    print_list(q -> list);
}









