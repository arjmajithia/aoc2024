#! /bin/sh 

FILE=compile_commands.json

if [ -f "$FILE" ]; then
	rm compile_commands.json;
fi
ln -s build/compile_commands.json . 
