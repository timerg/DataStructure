#include <stdio.h>
#include <stdlib.h>
#include "linked.h"





int main() {
    Node* list = cons(5, cons(4, cons(3, new())));
    int output = length(list);
    print_list(list);
    list = insert_at(9, 200, list);

    print_list(list);
    free_list(list);
    printf("%d\n", output);

    return 0;
}