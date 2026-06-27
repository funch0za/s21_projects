CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./include
LDFLAGS = -lncurses

TEST_CFLAGS = -g -I./include --coverage -O0
TEST_LDFLAGS = -lcheck -lm -lpthread -lncurses --coverage

INCLUDE_DIR = include
BIN_DIR = bin

SRCS = main.c frontend.c maze.c maze_image.c queue.c
OBJS = $(SRCS:.c=.o)

TEST_SRCS_NO_MAIN = frontend.c maze.c maze_image.c queue.c
TEST_OBJS = $(TEST_SRCS_NO_MAIN:.c=.gc.o)

TARGET = $(BIN_DIR)/maze
TEST_TARGET = $(BIN_DIR)/test_runner

PREFIX ?= /usr/local
INSTALL_DIR = $(DESTDIR)$(PREFIX)

.PHONY: all clean install uninstall tests gcov coverage help

all: directories $(TARGET)

directories:
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tests: directories $(TEST_TARGET)
	@echo "Running tests..."
	@$(TEST_TARGET)
	@echo "Tests completed"

$(TEST_TARGET): $(TEST_OBJS) tests/test_find_path.c
	$(CC) $(TEST_CFLAGS) $^ -o $@ $(TEST_LDFLAGS)

%.gc.o: %.c
	$(CC) $(TEST_CFLAGS) -c $< -o $@

gcov: clean tests
	@echo "Generating coverage report..."
	@if command -v gcovr >/dev/null 2>&1; then \
		gcovr --root . --html --html-details -o coverage.html \
			--exclude tests \
			--exclude main.c \
			--exclude frontend.c \
			--exclude queue.c; \
		echo "Coverage report generated at coverage.html"; \
	else \
		echo "WARNING: gcovr not installed. Generating raw gcov output..."; \
		gcov *.gcda *.gcno 2>/dev/null || true; \
		echo "Raw coverage data generated"; \
	fi

coverage: gcov
	@echo "Coverage analysis complete"

install: $(TARGET)
	@echo "Installing to $(INSTALL_DIR)/bin"
	@mkdir -p $(INSTALL_DIR)/bin
	@cp $(TARGET) $(INSTALL_DIR)/bin/
	@chmod 755 $(INSTALL_DIR)/bin/maze
	@echo "Installation complete"

uninstall:
	@echo "Removing from $(INSTALL_DIR)/bin"
	@rm -f $(INSTALL_DIR)/bin/maze
	@echo "Uninstallation complete"

clean:
	@echo "Cleaning object files and binaries..."
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
	@rm -f *.gcda *.gcno *.gcov
	@rm -rf $(BIN_DIR)
	@rm -f coverage.*
	@echo "Clean complete"

distclean: clean
	@echo "Removing all generated files..."
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
	@rm -rf $(BIN_DIR)
	@rm -f coverage.*
	@find . -name "*~" -delete
	@echo "Distclean complete"

help:
	@echo "Available targets:"
	@echo "  all         - Build the program (default)"
	@echo "  clean       - Remove object files and binaries"
	@echo "  distclean   - Remove all generated files"
	@echo "  install     - Install program to $(PREFIX)/bin"
	@echo "  uninstall   - Remove installed program"
	@echo "  tests       - Build and run unit tests"
	@echo "  gcov        - Run tests with coverage analysis"
	@echo "  coverage    - Generate coverage report"
	@echo "  help        - Show this help message"