#!/bin/bash
while true; do
    python3 ./test_data_gen.py > test.in #出数据
    ./a < test.in > a.out #被测程序
    python3 ./standard.py < test.in > standard.out #正确（暴力）程序
     if diff a.out standard.out; then
        printf "AC\n"
    else
        printf "Wa\n"
        exit 0
    fi
done