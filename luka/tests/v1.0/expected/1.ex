int array: a (size: 10)
int var: i = 0
int ref var: mypointer
int ref array: pointers (size: 2)
= mypointer [addr] i
= i + [ref] mypointer 1
= [index] pointers 0 mypointer
= [index] pointers 1 [addr] [index] a 3
int ref ref var: doublepointer
= doublepointer [addr] [index] pointers 0

