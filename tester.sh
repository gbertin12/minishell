#!/bin/bash

function test_string()
{
	echo " "
	echo "cmd = $1"
	echo "-------- RESULTAT ----------"
	./minishell -c "$1"
	echo -e "$1" | bash --posix
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

test_string 'echo toto'
export ls="ls" ls2="           ls"
test_string 'echo $ls$ls2'

# rm -rf output_posix output_tester