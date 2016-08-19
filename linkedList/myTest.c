#include <stdio.h>
#include <stdlib.h>
#include "linked.h"





int main() {
    Node* list = cons(3, cons(4, cons(5, cons(3, newNode()))));
    Node* list_2 = cons(4, cons(5, newNode()));
    Node* output = doKmp(list, list_2);


    print_list(output);
    free_list(output);

    free_list(list);
    free_list(list_2);
    return 0;
}