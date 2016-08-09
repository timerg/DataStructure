#ifndef __sufixTree
#define __sufixTree

#include "linked.h"

typedef struct SNode SNode;
typedef struct ListOfSNode ListOfSNode;
typedef struct SLeaf SLeaf;

ListOfSNode* consSN(SNode* newNode, ListOfSNode* list);
ListOfSNode* createSNlist();
ListOfSNode* theNthList(ListOfSNode* list, int position);
ListOfSNode* freeNthsnode(ListOfSNode* list, int position);


SNode* createKnot();
SNode* createRoot();
SNode* createSNode();
SNode* createLeaf(int depth, int position);
SNode* createAscend(SNode* node, Node* input, int n);
void createBranch(SNode* node, Node* input, int n, int label);
int compareListPrefix (ListOfSNode* list, int input);
SNode* thechild(SNode* node, int position);
SNode* updateChild(SNode* node, SNode* new, int position);
void createNode(SNode* tree, Node** index, Node* input, int length, int label);

void searchTree();
void compare(SNode* node, Node* input, int n);

void free_SNlist(ListOfSNode* list);
void freeSNode(SNode* snode);


#endif