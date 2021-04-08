#!/bin/bash

rm doubly_linked_list.o tests.o main.o zzz
clear
g++ doubly_linked_list.cpp -std=c++20 -Wall -Wextra -c -o doubly_linked_list.o
g++ tests.cpp -std=c++20 -Wall -Wextra -c -o tests.o
#g++ related_topics.cpp -std=c++20 -Wall -Wextra -c -o related_topics.o
g++ main.cpp -std=c++20 -Wall -Wextra -c -o main.o

g++ doubly_linked_list.o tests.o main.o -o zzz
./zzz
