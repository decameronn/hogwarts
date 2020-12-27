:: C99
@echo off
if not exist ..\build mkdir ..\build
pushd ..\build
gcc -Wall -Wmissing-prototypes -Wstrict-prototypes -Wextra -D -O2 -std=c99 -ggdb3 main.c -o hash_table_app
popd

