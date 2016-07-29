#ifndef _link
#define _link

#define NIL 0
#define CONS 1

typedef int NodeType;



typedef struct Node {
    NodeType type;
    // for CONS
    int val;
    struct Node* next;
} Node ;

Node* new();
Node* cons(int val, Node* xs);
Node* insert_at(int x, unsigned int n, Node *node) ;
int length(Node* node);
int sum(Node* xs);
void free_list(Node* xs);
void print_list(Node* xs);


#endif