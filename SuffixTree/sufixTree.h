#ifndef __sufixTree
#define __sufixTree

#include "linked.h"


#define MAX 10
#define ROOT -1
#define NODE 1
#define KNOT 0
#define LEAF -2

typedef struct SNode SNode;
typedef struct ListOfSNode ListOfSNode;
typedef struct SLeaf SLeaf;

typedef struct SNode {
    // ROOT, KNOT, NODE, LEAF
    int type;

    // ROOT, KNOT, NODE Only
    ListOfSNode* childrens;

    // ROOT, NODE Only. For LEAF it's '$'
    int edge;

    // NODE Only
    Node* label;

    // LEAF Only
    int position;
    int depth;

} SNode;


typedef struct ListOfSNode {
    int type;
    SNode* node;
    ListOfSNode* next;
} ListOfSNode;


ListOfSNode* consSN(SNode* newNode, ListOfSNode* list);
ListOfSNode* createSNlist();
ListOfSNode* theNthList(ListOfSNode* list, int position);
ListOfSNode* freeNthsnode(ListOfSNode* list, int position);


SNode* createKnot(int label);
SNode* createRoot();
SNode* createSNode();
SNode* createLeaf(int depth, int position);
SNode* createAscend(SNode* node, Node* input, int n, int label);
void createBranch(SNode* node, Node* input, int n, int label);
int findBranchIndex (ListOfSNode* list, int input);
SNode* thechild(SNode* node, int position);
SNode* updateChild(SNode* node, SNode* new, int position);
void createNode(SNode* tree, Node** index, Node* input, int length, int label);
void searchTree();
void compare(SNode* node, Node* input, int n);

void free_SNlist(ListOfSNode* list);
void freeSNode(SNode* snode);

void print_tree(SNode* tree, int indent);
void print_treeChildren(ListOfSNode* tree, int indent);
void print_label(SNode* tree, int indent);
void print_labelChildren(ListOfSNode* tree, int indent);

#endif