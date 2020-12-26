
:: C99
@echo off
gcc -M -Wall -Wmissing-prototypes -Wstrict-prototypes -Wextra -D _GNU_SOURCE -O2 -std=c99 -ggdb3 *.c -o ht_table_app

