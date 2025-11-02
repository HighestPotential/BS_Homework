#!/bin/bash

mkdir -p results

for f in 00_input 01_input 02_input 00_solution 01_solution 02_solution ; do
	if ! [ -e "$f" ]; then
		echo "There is no file $f in this directory. Make sure you download it (and the others), for this test to work."
		exit 1
	fi
done

if ! [ -e on_the_clock ]; then
	if ! make on_the_clock ; then
        echo "Compilation failed."
        exit 1
    fi
fi

tests_passed=0

for test in 00 01 02 ; do
	cat ${test}_input | ./on_the_clock 2> results/${test}_output
	if diff -q results/${test}_output ${test}_solution >/dev/null; then
		echo "Test ${test} passed."
		tests_passed=$((tests_passed+1))
	else
		echo "Test ${test} failed. Output differs from solution."
		diff results/${test}_output ${test}_solution
	fi
done

echo "$tests_passed/3 tests passed."

if [ "$tests_passed" = 3 ]; then
	echo "Congratulations!"
fi
