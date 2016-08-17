## Suffix Tree Building



### Briefly Complexity Discuss
The complexity of this Suffix Tree building algorithm is from O(n) to O(n^2)

This claim of complexity is based on how many times that new Node/Knob appending happens.

A Best case example: AAAAA$
  root
    |-> A
        |-> A
           |-> A
               |-> A
                   |-> A$
A Worst case example: ABCDE$
  root
    |-> A
        |-> B
            |-> C
                |-> D
                    |-> E$
    |-> B
        |-> C
            |-> D
                |-> E$
    |-> C
        |-> D
            |-> E$
    |-> D
        |-> E$
    |-> E$