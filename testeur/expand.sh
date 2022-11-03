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

export ls="ls" ls2="           ls"
echo "ls = 'ls'"
echo "ls2 = '             ls'"
test_string 'echo $ls$ls2'
test_string 'echo $ls2$ls'
test_string 'echo $ls'
test_string 'echo $ls2'
test_string '$ls$ls2'
echo " "
echo " "
export ls="ls" ls2="ls"
echo "ls = 'ls'"
echo "ls2 = 'ls'"
test_string 'echo  $ls$ls2'
test_string 'echo $ls $ls2'
test_string 'echo $ls toto $ls2'
test_string 'echo "$ls"$ls2'
test_string 'echo $ls"$ls2"'
test_string 'echo $ls "$ls2"'
test_string 'echo "$ls $ls2"'
test_string 'echo -n test $ls'
test_string 'echo -nnnn test $fef'
test_string '$ls$ls2'
test_string ""
test_string 'echo $USER"$USER"$USER'


# rm -rf output_posix output_tester