int var: a = 0, b = 1, c, d
bool var: teste_falso = false
if: > a b
then:
  if: > a 0
  then:
    = c 10
if: teste_falso
then:
  = d 0
else:
  = d 20

