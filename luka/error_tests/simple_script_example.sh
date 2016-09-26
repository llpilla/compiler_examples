#!/bin/bash
./lukacompiler < v0.1/input/1.in > usual_output 2> error_output
diff usual_output v0.1/expected/1.ex > output
echo "Differences between expected and generated outputs"
cat output
diff error_output v0.1/expected/1.ex_err > err_output
echo "Differences between expected and generated error outputs"
cat err_output

