#!/bin/bash
seed=$RANDOM


##########
# VS Null
# ./Game Null Null Null Testo -s 30 -i default.cnf -o aaaaROLLED.res
##########



##########
# VS Demo
./Game Demo Demo Demo Testo -s $seed -i default.cnf -o aaaaROLLED.res
##########
# echo fi;
##########
# VS Dummy
# ./Game Dummy Dummy Dummy Testo -s 30 -i default.cnf -o aaaaROLLED.res
##########

# ./GameTest.sh Testo Testo Testo Testo 5