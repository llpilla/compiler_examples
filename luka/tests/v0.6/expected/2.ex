int var: i, j
if: true
then:
  int var: i
  if: true
  then:
    for: = i 0, < i 10, = i + i 3
    do:
      int var: j

