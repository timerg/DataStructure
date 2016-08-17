/*
The complication of this SufixTree building algorithm is from O(n) to O(n^2) if creation of each size of branch takes same time.
ps. The statement after "if" means: This claim of complication is based on the steps that comparison takes.
    In other words: How many times the function "createNode" happens.
For a branch with size of n, it takes n time.

ignore the building time for
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sufixTree.h"
#include "linked.h"




void print_tree(SNode* tree, int indent){
    switch(tree -> type){
        case ROOT:
            indent = indent + 1;
            print_treeChildren(tree -> childrens, indent);
            break;
        case NODE:
            indent = indent + 1;
            printf(" %c\n", tree -> edge);
            print_treeChildren(tree -> childrens, indent);
            break;
        case KNOT:
            printf(" %c", tree -> edge);
            print_tree(tree -> childrens -> node, indent);
            break;
        case LEAF:
            printf(" $\n");
    }
}

void print_treeChildren(ListOfSNode* tree, int indent){
    if(tree -> type == NIL){
    } else {
        for(int i = 0; i < indent; i++){
            printf("  ");
        };
        print_tree(tree -> node, indent);
        print_treeChildren(tree -> next, indent);
    }
}

void print_label(SNode* tree, int indent){
    switch(tree -> type){
        case ROOT:
            indent = indent + 1;
            print_list(tree -> label);
            printf("\n");
            print_labelChildren(tree -> childrens, indent);
            break;
        case NODE:
            indent = indent + 1;
            print_list(tree -> label);
            printf("\n");
            print_labelChildren(tree -> childrens, indent);
            break;
        case KNOT:
            print_list(tree -> label);
            print_label(tree -> childrens -> node, indent);
            break;
        case LEAF:
            printf(" $\n");
    }
}

void print_labelChildren(ListOfSNode* tree, int indent){
    if(tree -> type == NIL){
    } else {
        for(int i = 0; i < indent; i++){
            printf("  ");
        };
        print_label(tree -> node, indent);
        print_labelChildren(tree -> next, indent);
    }
}



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

SNode* createKnot(int label){
    SNode* new = malloc(sizeof(SNode));
    new -> type = KNOT;
    new -> label = cons(label, newNode());
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

SNode* createAscend(SNode* node, Node* input, int n, int label) {
    if(n == 0){
        return(node);
    } else if (n > 0){
        SNode* new = createKnot(label);
        new -> type = KNOT;
        new -> edge = input -> val;
        new -> childrens = consSN(node, new -> childrens);
        return(createAscend(new, input -> next, n - 1, label));
    } else {
        exit(2);
    };
}

// for value n: if linked list = 2|1|$, n = 2. So an input n is at least 1.
void createBranch(SNode* node, Node* input, int n, int label){
    if(node -> type != ROOT) {
        node -> type = NODE;
    };
    if(node -> label -> val != label){
        node -> label = cons(label, node -> label);
    };

    SNode* leaf = createLeaf(1, n);
    if(n > 0){
        SNode* branchHead = createAscend(leaf, input -> next, n, label);
        node -> childrens = consSN(branchHead, node -> childrens);
    } else if(n == 0){
        node -> childrens = consSN(leaf, node -> childrens);
    } else exit(2);
}


// start from 1; if no match then give 0
int findBranchIndex (ListOfSNode* list, int input){
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
        int x = findBranchIndex(list -> next, input);
        if (x == 0){
            return(0);
        } else {
            return (1 + x);
        }
    }
}

/* The Hskell version for findBranchIndex:
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
    int branchIndex = findBranchIndex(tree -> childrens, (index[length]) -> val);
    if(tree -> type != LEAF){
        if(tree -> label -> type == NIL){
            tree -> label = cons(label, tree -> label);
        } else {
            if(tree -> label -> val != label){
                tree -> label = cons(label, tree -> label);
            }
        }
    }
    if(branchIndex == 0){
        // printf("[No match, create new branch\n");
        createBranch(tree, input, length, label);
    } else if(branchIndex == -1){
        tree -> childrens = consSN(createLeaf(1, length), tree -> childrens);
    } else {
        // printf("Match, find descend\n");
        createNode(thechild(tree, branchIndex), index, input, length - 1, label);
    }
}






