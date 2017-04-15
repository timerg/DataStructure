#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

// data List = Nil              -- type = NIL
//           | Cons Int List    -- type = CONS






// smart constructor
Node* newNode() {
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

Node* pop(Node* xs){
    if(xs -> type == CONS){
        Node* temp = xs -> next;
        free(xs);
        return temp;
    } else if(xs -> type == NIL){
        return xs;
    } else {
        printf("list Type error\n");
        exit(2);
    }
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
        return cons(x, node);
    } else {
        if (n == 0) {
            return (cons(x, node));
        } else {
            node -> next = insert_at(x, (n - 1), node -> next);
            return node;
        }
    }
}

// ex delete_at 1 :  a|b|c|NIL  -> a|c|NIL
Node* delete_at(unsigned int n, Node *node) {
    if (node -> type == NIL) {
        printf("list reach the end\n");
        return node;
    } else {
        if (n == 0) {
            Node* temp = node -> next;
            free(node);
            return temp;
        } else {
            node -> next = delete_at((n - 1), node -> next);
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
        printf("[] ");
    } else {
        // Cons
        printf("%d ", xs -> val);
        print_list(xs -> next);
    }
}

void print_listc(Node* xs) {
    if (xs -> type == NIL) {
        // Nil
        printf("[]\n");
    } else {
        // Cons
        printf("%c", xs -> val);
        print_listc(xs -> next);
    }
}

void indexNode(Node** index, Node* list, int i){
    if(list -> type != NIL){
        index[i] = list;
        indexNode(index, list -> next, i + 1);
    }
}

int ifexist(Node* node, int input){
    if(node -> type == NIL){
        return 0;
    } else if(node -> val == input){
        return 1;
    } else {
        return ifexist(node -> next, input);
    }
}

int ifexistAll(Node* node, Node* input){
    if(input -> next -> type == NIL){
        return ifexist(node, input -> val);
    } else {
        return (ifexist(node, input -> val) && ifexistAll(node, input -> next));
    }
}

void copylist_(Node* node1, Node* node2){
    if(node2 -> type == NIL){
        Node* new = malloc(sizeof(Node));
        new -> type = NIL;
        node1 -> next = new;
    } else{
        Node* new = malloc(sizeof(Node));
        new -> type = CONS;
        new -> val = node2 -> val;
        node1 -> next = new;
        copylist_(new, node2 -> next);
    }
}


Node* reverse_(Node* node1, Node* node2){
    if(node1 -> type == NIL){
        free_list(node1);
        return node2;
    } else {
        Node* temp = node1 -> next;
        Node* output = reverse_(temp, cons(node1 -> val, node2));
        free(node1);
        return output;
    }
}

Node* reverse (Node* node){
    Node* node2 = newNode();
    Node* out = reverse_(node, node2);
    return out;
}

Node* copylist(Node* node){
    Node* new = malloc(sizeof(Node));
    new -> type = CONS;
    new -> val = node -> val;
    copylist_(new, node -> next);
    return new;
}

//---- KMP ----//
int* kmp_table(Node** w, int l_w){
    int* table = malloc(l_w * sizeof(int));
    table[0] = -1;
    table[1] = 0;
    int i = 0;
    int j = 2;
    while(j < l_w){
        if(w[j - 1] -> val == w[i] -> val){
            i = i + 1;
            table[j] = i;
            j = j + 1;
        } else if(i > 0){
            i = table[i];
        } else {
            table[j] = 0;
            j = j + 1;
        }
    }
    return table;
}

int kmp_search(Node** s, Node** w, int* table, int l_s, int l_w, int start){
    int m = start;
    int i = 0;
    while (m + i < l_s){
        if(w[i] -> val == s[m + i] -> val){
            if(i == l_w - 1){
                return m;
            }
            i = i + 1;
        } else{
            if(table[i] > -1){
                m = m + i - table[i];
                i = table[i];
            } else{
                m = m + 1;
                i = 0;
            }
        }
    }
    return l_s;
}

// Ex: list1 = GUACUAC[]; list2 = AC[]
// Result = 3, 6

Node* doKmp(Node* list1, Node* list2){

    int l_1 = length(list1);
    int l_2 = length(list2);
    Node* index1[l_1];
    indexNode(index1, list1, 0);
    Node* index2[l_2];
    indexNode(index2, list2, 0);
    int* table = kmp_table(index2, l_2);
    int p = 0;
    Node* output = newNode();
    loop:
        p = kmp_search(index1, index2, table, l_1, l_2, p);
        if(p == l_1){
            goto stop;
        }
        output = cons(p, output);
        p++;
        goto loop;
    stop:
    free(table);
    return output;
}


//---- --- ----//