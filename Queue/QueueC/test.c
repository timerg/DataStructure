#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int main(){
    Que* q1 = new_Queue();
   // q1 = enque(2, q1);
    q1 = enque(3, enque(2, q1));
    // q1 = deque(q1);
    print_Queue(q1);
    printf("%d\n", sizeofQueue(q1));
   //  printf("%d\n", pop(deque(q1)));
    free_list(q1);
    return 0;
}