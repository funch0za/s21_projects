CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 -g

all: s21_cat

s21_cat: main.c
	$(CC) $(FLAGS) main.c -o s21_cat 

test: s21_cat
	bash test_cat.sh

clean:
	rm -rf s21_cat
