PROJECT=s21_matrix

CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11 -g

SOURCE=./s21_matrix.c ./s21_matrix_help.c
TARGET=$(PROJECT).a
AR=ar
ARFLAGS=rc
RLIB=ranlib

all: clean $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -c $(CFLAGS) $^
	$(AR) $(ARFLAGS) $@ *.o
	$(RLIB) $@

TSTDIR=./test
TST=$(shell find $(TSTDIR) -depth -name '*.c')
TESTER=test_$(PROJECT)
LFLAGS = -lcheck

ifeq ($(shell uname -s),Linux)
	LFLAGS  += -pthread -lrt -lm -lsubunit
endif

# for Alpine
ifeq ($(shell uname -o),Linux)
	LFLAGS = -lcheck
endif

test: $(TST) $(TARGET)
	$(CC) $(CFLAGS) $^ -o $(TESTER) $(LFLAGS)
	./$(TESTER)	

gcov_report:
	$(CC) $(SOURCE) $(TST) -fprofile-arcs -ftest-coverage --coverage $(LFLAGS) $(CFLAGS) -o $(TESTER)
	./$(TESTER)	
	rm test_$(PROJECT)-test*.gcda
	rm test_$(PROJECT)-test*.gcno
	rm test_$(PROJECT)-s21_help_func_test.gcda
	rm test_$(PROJECT)-s21_help_func_test.gcno
	gcovr -r . --html --html-details  -o report.html

clean:
	rm -f *.o $(TARGET) $(TESTER) $(TSTDIR)/logs/*.log *.gcno *.html *.css *.gcda *gcno
	rm -rf *.dSYM

.PHONY: clean all test
