#ifndef _queue_h
#define _queue_h

typedef int NodeType;

#define CONS 1
#define NIL 0

typedef struct Node {
    NodeType type;
    int val;
    struct Node* next;
} Node ;

typedef struct Que {
    Node *list;
    Node *rear;

} Que ;

void free_Node(Node *n);
Node* nil() ;
void print_list(Node *n) ;
int length_node(Node *n);

Que* new_Queue();
void free_list(Que *q);
int is_empty(Que *q);
Que *enque(int val, Que *q);
Que *deque(Que *q);
int pop(Que *q);
void print_Queue(Que *q);

#endif