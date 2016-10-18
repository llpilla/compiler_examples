# Łukasiewicz tests

* Run lukacompiler passing an input using "<" and saving its output using ">". Example:

    `./lukacompiler < tests/v0.1/input/1.in > 1.out`

* Compare the output with the expected output using diff. Example:

    `diff 1.out tests/v0.1/expected/1.ex`

* If any differences are found, your compiler is not respecting the project specification.

* You may use the `batch_test.sh` script to automate this process:

    `./batch_test.sh /path/to/lukacompiler`

  One may find it useful to redirect stderr to `/dev/null` and pipe the script
  output to a pager.
