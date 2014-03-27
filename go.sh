#!/bin/bash

# compile le programme puis le lance

make clean
make
./bin/dpll test.data

exit 0
