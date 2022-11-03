#!/bin/bash

function test_string()
{
	echo " "
	echo "cmd = $1"
	echo "-------- RESULTAT ----------"
	echo "mini :"
	./../minishell -c "$1"
	echo " "
	echo "bash :"
	echo -e "$1" | bash --posix
	echo " "
	echo "----------------------------"
	echo " "
	# DIFF=$(diff output_tester output_posix)
	# if [[ $DIFF == "" ]] 
	# then
	# 	echo "OK"
	# else
	# 	echo "FAILURE : '$1'" 
	# fi
}

test_string "$34"
test_string 'cat"ls"'
test_string 'cat Makefile | wc >'
test_string 'cat Makefile | wc <'
test_string 'cat Makefile | wc |'
# zsh 
test_string 'export | wc -l'
test_string 'env | wc -l'
test_string 

