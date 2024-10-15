CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 -g

all: s21_grep

s21_grep: main.c
	$(CC) $(FLAGS) main.c -o s21_grep

test: s21_grep
	bash grep_test.sh

run_valgrind:
	bash grep_tests_valgrind.sh 

run_leaks:
	bash grep_tests_leaks.sh

clean:
	rm -rf s21_grep
