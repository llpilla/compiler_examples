int fun: fibo (params: int x, bool b)
  int var: ans
  if: < x 2
  then:
    = ans x
  else:
    = ans + fibo[2 params] - x 1 b fibo[2 params] - x 2 b
  ret ans
int var: a
= a fibo[2 params] 10 true

