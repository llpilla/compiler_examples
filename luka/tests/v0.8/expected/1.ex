int array: a (size: 10)
bool array: parity (size: 10)
for: = i 0, < i 10, = i + i 1
do:
  = [index] a i i
 if: == / [index] a i 2 0
  then:
    = [index] parity i true
  else:
    = [index] parity i false

