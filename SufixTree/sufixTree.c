/*
The complication of this SufixTree building algorithm is from O(n) to O(n^2) if creation of each size of branch takes same time.
ps. The statement after "if" means: This claim of complication is based on the steps that comparison takes.
    In other words: How many times the function "createNode" happens.
For a branch with size of n, it takes n time.

ignore the building time for
*/


#include <stdio.h>
#include <stdlib.h>
#include "sufixTree.h"
#include "linked.h"
#include "dbg.h"


#define MAX 10
#define ROOT -1
#define NODE 1
#define KNOT 0
#define LEAF -2


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



void free_SNlist(ListOfSNode* list){
    if (list -> type == NIL) {
        free(list);
    } else {
        free_SNlist(list -> next);
        freeSNode(list -> node);
        free(list);
    }
}

void freeSNode(SNode* snode){
    if(snode -> type != LEAF) free_list(snode -> label);
    free_SNlist(snode -> childrens);
    free(snode);
}

ListOfSNode* consSN(SNode* newNode, ListOfSNode* list){
    ListOfSNode* nextListSN = malloc(sizeof(ListOfSNode));
    nextListSN -> type = CONS;
    nextListSN -> node = newNode;
    nextListSN -> next = list;
    return(nextListSN);
}

ListOfSNode* createSNlist(){
    ListOfSNode* new = malloc(sizeof(ListOfSNode));
    new -> type = NIL;
    return(new);
}

void print_SNlist(ListOfSNode* list){
    if(list -> type == NIL){
        // printf("%c ", list -> node -> edge);
    } else {
        printf("%c ", list -> node -> edge);
        print_SNlist(list -> next);
    }
}

void print_SN1stChildren(SNode* node){
    if(node -> type == LEAF){
        printf("%c \n", node -> edge);
    } else if (node -> type == ROOT){
        printf("'ROOT' ");
        print_SN1stChildren(node -> childrens -> node);
    } else {
        printf("%c ", node -> edge);
        print_SN1stChildren(node -> childrens -> node);
    }
}


ListOfSNode* theNthList(ListOfSNode* list, int position){
    if(position == 1){
        // printf("%d\n", list -> node -> edge);
        return(list);
    } else if(position < 0){
        printf("negative position || Index failed\n");
        exit(2);
    } else{
        return(theNthList(list -> next, position - 1));
    }
}

// Remove the Nth child of a list of childrens.
ListOfSNode* freeNthsnode(ListOfSNode* list, int position){
    if(position == 1){
        ListOfSNode* temp = list -> next;
        freeSNode(list -> node);
        free(list);
        return(temp);
    } else if(position > 1){
        ListOfSNode* targetParent = theNthList(list, position - 1);
        ListOfSNode* target = targetParent -> next;
        targetParent -> next = target -> next;
        freeSNode(target -> node);
        free(target);
        return(list);
    } else {
        printf("Wrong position information\n");
        exit(2);
    }
}

SNode* createKnot(){
    SNode* new = malloc(sizeof(SNode));
    new -> type = KNOT;
    new -> label = newNode();
    new -> childrens = createSNlist();
    return(new);
}

SNode* createRoot(){
    SNode* new = malloc(sizeof(SNode));
    new -> type = ROOT;
    new -> label = newNode();
    new -> childrens = createSNlist();
    return(new);
}

SNode* createLeaf(int depth, int position){
    SNode* leaf = malloc(sizeof(SNode));

    // This initilization is needed or the free_SNlist function screams.
    leaf -> childrens = createSNlist();
    leaf -> type = LEAF;
    leaf -> edge = '$';
    leaf -> depth = depth;
    leaf -> position = position;
    return(leaf);
}

SNode* createAscend(SNode* node, Node* input, int n) {
    if(n == 0){
        return(node);
    } else if (n > 0){
        SNode* new = createKnot();
        new -> type = KNOT;
        new -> edge = input -> val;
        // printf("[CREATEASCEND] edge is %c\n", input -> val);
        new -> childrens = consSN(node, new -> childrens);
        return(createAscend(new, input -> next, n - 1));
    } else {
        exit(2);
    };
}

// for value n: if linked list = 2|1|$, n = 2. So an input n is at least 1.
void createBranch(SNode* node, Node* input, int n, int label){
    if(node -> type != ROOT) {
        node -> type = NODE;
    };
    if(!ifexist(node -> label, label)) {
        node -> label = cons(label, node -> label);
    };

    SNode* leaf = createLeaf(1, n);
    if(n > 0){
        // SNode* end = createKnot();
        // end -> childrens = consSN(leaf, end -> childrens);
        // end -> edge = input -> next -> val;
        // SNode* branchHead = createAscend(end, input -> next -> next, n - 1);
        // node -> childrens = consSN(branchHead, node -> childrens);

        SNode* branchHead = createAscend(leaf, input -> next, n);
        // printf("[CREATEBRANCH] BranchHead = %c \n", branchHead -> edge);
        node -> childrens = consSN(branchHead, node -> childrens);
    } else if(n == 0){
        printf("[CREATEBRANCH] LEAF Only created\n");
        node -> childrens = consSN(leaf, node -> childrens);
    } else exit(2);
}


// start from 1; if no match then give 0
int compareListPrefix (ListOfSNode* list, int input){
    if (list -> type == NIL){
        return(0);
    }
    else if(input == list -> node -> edge){
        if(input == '$'){
            return(-1);
        } else {
            return(1);
        }
    } else {
        if (compareListPrefix(list -> next, input) == 0){
            return(0);
        } else {
            return (1 + compareListPrefix(list -> next, input));
        }
    }
}

/* The Hskell version for compareListPrefix:
findlist :: Int -> [Int] -> Maybe Int
findlist x [] = Nothing
findlist x (s:xs) = if x == s then Just 1
    else
        case findlist x xs of
            Nothing -> Nothing
            Just a -> Just (1 + a)
*/


SNode* thechild(SNode* node, int position){
    ListOfSNode* theList = theNthList(node -> childrens, position);

    return (theList -> node);
}


/*
Note that the "order" of children will change. the updated one will be put infront
*/
SNode* updateChild(SNode* node, SNode* new, int position){
    node -> childrens = freeNthsnode(node -> childrens, position);
    node -> childrens = consSN(new, node -> childrens);
    return(node);
};


/*
Compare the first value of a newly input Snode with Prefixes(only the first value) of other child.
If no one matches, simply create a new branch
If the nth child match,
    Copy that child and let the new child's children be the new tree for function createTree.
        Do the recursive operation.
    Kill the old one and paste the newone. (updateChild)
*/
void createNode(SNode* tree, Node** index, Node* input, int length, int label){
    printf("[CREATENODE]: %c\n", index[length] -> val);
    int comparison = compareListPrefix(tree -> childrens, (index[length]) -> val);
    if(comparison == 0){
        printf(" comparison no match, length now = %d\n", length);
        createBranch(tree, input, length, label);
    } else if(comparison == -1){
        printf(" comparison reach $\n");
        tree -> childrens = consSN(createLeaf(1, length), tree -> childrens);
    } else {
        printf(" comparison match\n");
        if(tree -> type != LEAF && !ifexist(tree -> label, label)){
                tree -> label = cons(label, tree -> label);
        }
        createNode(thechild(tree, comparison), index, input -> next, length - 1, label);
    }
}




int main() {
    FILE* file;
    file = fopen("data", "r");
    Node* inputList = newNode();
    FILE* file1;
    file1 = fopen("data1", "r");
    Node* inputList1 = newNode();
    int inputList_length = 0;
    int base;
    while((base = fgetc(file)) != EOF){
        inputList = cons(base, inputList);
        inputList_length = inputList_length + 1 ;
    };
    inputList = cons('$', inputList);
    int inputList_length1 = 0;
    while((base = fgetc(file1)) != EOF){
        inputList1 = cons(base, inputList1);
        inputList_length1 = inputList_length1 + 1 ;
    };
    inputList1 = cons('$', inputList1);

/* The index is needed
to make comparison(new sufix compare with existed branches' prefix).
    Because the head of the new sufix is burried at the bottom of linked list(stack).
This should be optimized by double Queue.
*/
    Node* index[sizeof(Node) * inputList_length];
    indexNode(index, inputList, 0);
    Node* index1[sizeof(Node) * inputList_length1];
    indexNode(index1, inputList1, 0);


    SNode* tree = createRoot();

    createBranch(tree, inputList, 1, 0);



    int i = 1;
    while (i <= inputList_length) {
        createNode(tree, index, inputList, i, 0);
        i = i + 1;
    }


    int j = 1;
    while (j <= inputList_length1) {
        createNode(tree, index1, inputList1, j, 1);
        j = j + 1;
    }


    freeSNode(tree);
    free_list(inputList);
    free_list(inputList1);
    fclose(file);
    fclose(file1);
    return(0);
}