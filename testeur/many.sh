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
}

test_string "echo toto | rev"
test_string "echo toto | rev | cat"
test_string "ls"

mkdir -p denied/test

test_string "ls denied"
chmod 000 denied
test_string "ls denied"

touch test

test_string "env > test"
chmod 000 test
echo "remove permission"
test_string "env > test"
test_string "pwd"
test_string '$ffr'
test_string '$fef ls'
test_string 'badcmd'

rm -f test
chmod 777 denied
rm -rf denied
