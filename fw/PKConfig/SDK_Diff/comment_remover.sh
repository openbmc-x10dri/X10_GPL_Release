#!/bin/sh

while true
do
#echo "Do you want to remove all comments from source codes ? (y/n)"
#read user_input

user_input='y'

if [[ $user_input = 'y' ]] || [[ $user_input = 'yes' ]] ; then

g++ -o ./comment_remover ./comment_remover.cpp

find ./ -iname "*.c" | xargs -n 1 ./comment_remover
find ./ -iname "*.h" | xargs -n 1 ./comment_remover
find ./ -iname "*.cpp" | xargs -n 1 ./comment_remover
find ./ -iname "*.java" | xargs -n 1 ./comment_remover
find ./ -iname "*.cc" | xargs -n 1 ./comment_remover
#find ./ -iname "*.js" | sed "/\/str\//d" | xargs -n 1 ./remove_comment

rm -f ./comment_remover

break

else
	if [[ $user_input = 'n' ]] || [[ $user_input = 'no' ]] ; then
		break
	fi
fi

done
