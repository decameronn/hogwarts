
@echo off
rem C99
:: if not exist ..\build mkdir ..\build
:: pushd ..\build
gcc *.c -Wall -Wmissing-prototypes -Wstrict-prototypes -Wextra -O2 -std=c99 -ggdb3 -o hash_table_app
:: popd
