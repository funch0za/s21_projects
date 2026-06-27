CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
#CFLAGS = -g -O0 -fsanitize=address
AR = ar
ARFLAGS = rcs
RANLIB = ranlib
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    CHECK_LIBS = -lcheck -lm -lrt -lpthread -lsubunit
else ifeq ($(UNAME_S), Darwin)
    CHECK_LIBS = -lcheck -lm
endif

INCLUDE_DIR = include
SRC_DIRS = s21_graph s21_graph_algorithms stack queue
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = tests
GCOVR_DIR = gcovr_report

S21_GRAPH_SRC = s21_graph/s21_graph.c
S21_GRAPH_ALGORITHMS_SRC = s21_graph_algorithms/s21_graph_algorithms.c
STACK_SRC = stack/stack.c
QUEUE_SRC = queue/queue.c

S21_GRAPH_OBJ = $(OBJ_DIR)/s21_graph.o
S21_GRAPH_ALGORITHMS_OBJ = $(OBJ_DIR)/s21_graph_algorithms.o
STACK_OBJ = $(OBJ_DIR)/stack.o
QUEUE_OBJ = $(OBJ_DIR)/queue.o

S21_GRAPH_LIB = $(LIB_DIR)/libs21_graph.a
S21_GRAPH_ALGORITHMS_LIB = $(LIB_DIR)/libs21_graph_algorithms.a
STACK_LIB = $(LIB_DIR)/libstack.a
QUEUE_LIB = $(LIB_DIR)/libqueue.a

HEADERS = $(INCLUDE_DIR)/s21_graph.h \
          $(INCLUDE_DIR)/s21_graph_algorithms.h \
          $(INCLUDE_DIR)/stack.h \
          $(INCLUDE_DIR)/queue.h \
          $(INCLUDE_DIR)/navigator_err.h

TEST_SRC = $(TEST_DIR)/test_s21_graph.c
TEST_BIN = $(TEST_DIR)/test_runner

NAVIGATOR_SRC = main.c
NAVIGATOR_BIN = s21_navigator

.PHONY: all clean test gcovr s21_navigator s21_graph s21_graph_algorithms

all: $(LIB_DIR) $(S21_GRAPH_LIB) $(S21_GRAPH_ALGORITHMS_LIB) $(STACK_LIB) $(QUEUE_LIB)

s21_graph: $(LIB_DIR) $(S21_GRAPH_LIB)

s21_graph_algorithms: $(LIB_DIR) $(S21_GRAPH_ALGORITHMS_LIB)

s21_navigator: $(LIB_DIR) $(S21_GRAPH_LIB) $(S21_GRAPH_ALGORITHMS_LIB) $(STACK_LIB) $(QUEUE_LIB) $(NAVIGATOR_SRC)
	$(CC) $(CFLAGS) $(NAVIGATOR_SRC) -o $(NAVIGATOR_BIN) \
		-I$(INCLUDE_DIR) \
		-L$(LIB_DIR) \
		-ls21_graph -ls21_graph_algorithms -lstack -lqueue

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(S21_GRAPH_LIB): $(OBJ_DIR) $(S21_GRAPH_OBJ)
	$(AR) $(ARFLAGS) $@ $(S21_GRAPH_OBJ)
	$(RANLIB) $@

$(S21_GRAPH_OBJ): $(S21_GRAPH_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(S21_GRAPH_ALGORITHMS_LIB): $(OBJ_DIR) $(S21_GRAPH_ALGORITHMS_OBJ)
	$(AR) $(ARFLAGS) $@ $(S21_GRAPH_ALGORITHMS_OBJ)
	$(RANLIB) $@

$(S21_GRAPH_ALGORITHMS_OBJ): $(S21_GRAPH_ALGORITHMS_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(STACK_LIB): $(OBJ_DIR) $(STACK_OBJ)
	$(AR) $(ARFLAGS) $@ $(STACK_OBJ)
	$(RANLIB) $@

$(STACK_OBJ): $(STACK_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(QUEUE_LIB): $(OBJ_DIR) $(QUEUE_OBJ)
	$(AR) $(ARFLAGS) $@ $(QUEUE_OBJ)
	$(RANLIB) $@

$(QUEUE_OBJ): $(QUEUE_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(S21_GRAPH_LIB) $(S21_GRAPH_ALGORITHMS_LIB) $(STACK_LIB) $(QUEUE_LIB)
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) \
		-I$(INCLUDE_DIR) \
		-L$(LIB_DIR) \
		-ls21_graph -ls21_graph_algorithms -lstack -lqueue \
		$(CHECK_LIBS)

gcovr: CFLAGS += $(GCOV_FLAGS)
gcovr: clean $(LIB_DIR) $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(S21_GRAPH_SRC) -o $(OBJ_DIR)/s21_graph.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(S21_GRAPH_ALGORITHMS_SRC) -o $(OBJ_DIR)/s21_graph_algorithms.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(STACK_SRC) -o $(OBJ_DIR)/stack.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(QUEUE_SRC) -o $(OBJ_DIR)/queue.o
	$(AR) $(ARFLAGS) $(S21_GRAPH_LIB) $(OBJ_DIR)/s21_graph.o
	$(AR) $(ARFLAGS) $(S21_GRAPH_ALGORITHMS_LIB) $(OBJ_DIR)/s21_graph_algorithms.o
	$(AR) $(ARFLAGS) $(STACK_LIB) $(OBJ_DIR)/stack.o
	$(AR) $(ARFLAGS) $(QUEUE_LIB) $(OBJ_DIR)/queue.o
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) \
		-I$(INCLUDE_DIR) \
		-L$(LIB_DIR) \
		-ls21_graph -ls21_graph_algorithms -lstack -lqueue \
		$(CHECK_LIBS)
	./$(TEST_BIN)
	mkdir -p $(GCOVR_DIR)
	gcovr --root . --html --html-details -o $(GCOVR_DIR)/coverage_report.html \
		--filter '.*s21_graph\.c' --filter '.*s21_graph_algorithms\.c'
	@echo "Report - $(GCOVR_DIR)/coverage_report.html"

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TEST_BIN) $(NAVIGATOR_BIN)
	rm -f *.gcda *.gcno *.gcov
	rm -rf $(GCOVR_DIR)
	rm -rf tests/*.gcda tests/*.gcno tests/*.gcov
