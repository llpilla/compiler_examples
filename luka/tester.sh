#!/bin/bash
# This script tests the projects developed by the students of INE5426

FISHGROUPS="anchova bacalhau carpa dourado enguia lambari salmao"
VERSIONS="v0.1 v0.2 v0.3 v0.4 v0.5 v0.6 v0.7 v0.8 v1.0"

for g in $FISHGROUPS #for each group
do
    echo "##### Group "$g
    run="./$g/projeto1/lukacompiler"
    for v in $VERSIONS  #for all versions of the compiler
    do
        echo "### Testing" $v
        if [ -d luka/tests/$v/input ] #if there are inputs
        then
            INPUTS=`ls luka/tests/$v/input`
            for i in $INPUTS
            do
                echo "** Test" $i
                #input file
                in="luka/tests/$v/input/$i"
                #expected output file
                exp="luka/tests/$v/expected/"`echo $i | sed s:in:ex:`
                $run < $in > outfile 2> errorfile
                diff -B outfile $exp
                if [ -s errorfile ]
                then
                    echo "* Unexpected errors found"
                    cat errorfile
                    echo
                fi
            done
        fi
    done
    echo "##### End "$g
    echo 
done
