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

Node* newNode();
Node* cons(int val, Node* xs);
Node* pop(Node* xs);
Node* insert_at(int x, unsigned int n, Node *node);
Node* delete_at(unsigned int n, Node *node);
int length(Node* node);
int sum(Node* xs);
void free_list(Node* xs);
void print_list(Node* xs);
void print_listc(Node* xs);
void indexNode(Node** index, Node* list, int i);
int ifexist(Node* node, int input);
int ifexistAll(Node* node, Node* input);
Node* reverse (Node* node);
Node* copylist(Node* node);

//---- KMP ----//
int* kmp_table(Node** w, int l_w);
int kmp_search(Node** s, Node** w, int* table, int l_s, int l_w, int start);
Node* doKmp(Node* list1, Node* list2);
//---- --- ----//
#endif