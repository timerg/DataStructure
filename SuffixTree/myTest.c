#include <stdlib.h>
#include <stdio.h>
#include "myTest.h"

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


    SNode* testNode = tree -> childrens -> next -> node;
    printf("edge is %c\n", (testNode -> edge));
    printf("type is %d\n", (testNode -> type));
    printf("It has labels: ");
    print_list(testNode -> label);



    // Node* Nodetest = cons(101, cons(102, cons(103, cons(104, newNode()))));
    // // Node* Nodetest = newNode();
    // print_listc(insert_at(105, 1, Nodetest));
    // printf("%c\n", 103);

    freeSNode(tree);
    free_list(inputList);
    free_list(inputList1);
    fclose(file);
    fclose(file1);
    return(0);
}