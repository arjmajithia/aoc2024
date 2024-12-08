#!/bin/sh

mkdir -p build; cd build/; 

case "${1}" in
  "1")
    cmake --fresh .. -DPART1=ON; 
    ;;
  "2")
    cmake --fresh ..; 
    ;;
  *)
    echo "Invalid part"
    exit
    ;;
esac

make; cd ..;

FILE=compile_commands.json

if [ -f "$FILE" ]; then
	rm compile_commands.json
fi
ln -s build/compile_commands.json . 
