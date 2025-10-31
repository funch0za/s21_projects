# Compiler and flags
CXX = g++
CC = gcc
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -Wno-sign-compare
CFLAGS = -std=c11 -Wall -Werror -Wextra -std=c99

# Installation directories
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
DATADIR = $(PREFIX)/share
DOCDIR = $(DATADIR)/doc/brick_game
MANDIR = $(DATADIR)/man/man6

# Directories
SRC_DIR = .
BRICK_GAME_DIR = brick_game
APP_DIR = app
GUI_CLI_DIR = gui/cli
GUI_DESKTOP_DIR = gui/desktop
BUILD_DIR = build
LIB_DIR = $(BUILD_DIR)/lib
OBJ_DIR = $(BUILD_DIR)/obj
DIST_DIR = dist
DOC_SRC_DIR = docs

# Targets
TARGET_CLI = brick_game_v2
TARGET_DESKTOP = brick_game_v2_desktop

# Source files
SNAKE_SOURCES_CPP = \
	$(BRICK_GAME_DIR)/snake/controller/snake_controller.cpp \
	$(BRICK_GAME_DIR)/snake/model/snake_model.cpp

TETRIS_SOURCES_C = \
	$(BRICK_GAME_DIR)/tetris/tetris_connect.c \
	$(BRICK_GAME_DIR)/tetris/tetris_figure.c \
	$(BRICK_GAME_DIR)/tetris/tetris_game_machine.c \
	$(BRICK_GAME_DIR)/tetris/tetris_map.c \
	$(BRICK_GAME_DIR)/tetris/tetris_matrix_operations.c \
	$(BRICK_GAME_DIR)/tetris/tetris.c

APP_SOURCES_CPP = \
	$(APP_DIR)/app.cpp \
	$(APP_DIR)/main.cpp

GUI_CLI_SOURCES_CPP = \
	$(GUI_CLI_DIR)/snake/snake_cli.cpp

GUI_CLI_SOURCES_C = \
	$(GUI_CLI_DIR)/tetris/tetris_cli.c \
	$(GUI_CLI_DIR)/tetris/tetris_input.c

GUI_DESKTOP_SOURCES_CPP = \
	$(GUI_DESKTOP_DIR)/snake/snake_desktop.cpp

GUI_DESKTOP_SOURCES_C = \
	$(GUI_DESKTOP_DIR)/tetris/tetris_desktop.c

# Object files
SNAKE_OBJS = $(addprefix $(OBJ_DIR)/,$(SNAKE_SOURCES_CPP:.cpp=.o))
TETRIS_OBJS = $(addprefix $(OBJ_DIR)/,$(TETRIS_SOURCES_C:.c=.o))
APP_OBJS = $(addprefix $(OBJ_DIR)/,$(APP_SOURCES_CPP:.cpp=.o))
GUI_CLI_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(GUI_CLI_SOURCES_CPP:.cpp=.o))
GUI_CLI_C_OBJS = $(addprefix $(OBJ_DIR)/,$(GUI_CLI_SOURCES_C:.c=.o))
GUI_DESKTOP_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(GUI_DESKTOP_SOURCES_CPP:.cpp=.o))
GUI_DESKTOP_C_OBJS = $(addprefix $(OBJ_DIR)/,$(GUI_DESKTOP_SOURCES_C:.c=.o))

GUI_CLI_OBJS = $(GUI_CLI_CPP_OBJS) $(GUI_CLI_C_OBJS)
GUI_DESKTOP_OBJS = $(GUI_DESKTOP_CPP_OBJS) $(GUI_DESKTOP_C_OBJS)

# Static library
STATIC_LIB = $(LIB_DIR)/libbrickgame.a

# Include directories
INCLUDES = \
	-I$(BRICK_GAME_DIR)/snake/common \
	-I$(BRICK_GAME_DIR)/snake/controller \
	-I$(BRICK_GAME_DIR)/snake/model \
	-I$(BRICK_GAME_DIR)/tetris \
	-I$(APP_DIR) \
	-I$(GUI_CLI_DIR) \
	-I$(GUI_CLI_DIR)/snake \
	-I$(GUI_CLI_DIR)/tetris \
	-I$(GUI_DESKTOP_DIR) \
	-I$(GUI_DESKTOP_DIR)/snake

# GTK flags (добавлено отдельно)
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)

# Library flags
NCURSES_FLAGS = -lncurses

# Default target
all: clean 
	$(MAKE) cli
	rm -rf $(BUILD_DIR)
	$(MAKE) desktop

# CLI target
cli: CXXFLAGS += -DCLI_UI
cli: CFLAGS += -DCLI_UI
cli: $(TARGET_CLI)

# Desktop target - добавляем GTK флаги
desktop: CXXFLAGS += -DDESKTOP_UI $(GTK_CFLAGS)
desktop: CFLAGS += -DDESKTOP_UI $(GTK_CFLAGS)
desktop: $(TARGET_DESKTOP)

# Build CLI executable
$(TARGET_CLI): $(STATIC_LIB) $(APP_OBJS) $(GUI_CLI_OBJS)
	$(CXX) $(CXXFLAGS) $(APP_OBJS) $(GUI_CLI_OBJS) -L$(LIB_DIR) -lbrickgame -o $@ $(NCURSES_FLAGS)

# Build Desktop executable - добавляем GTK библиотеки
$(TARGET_DESKTOP): $(STATIC_LIB) $(APP_OBJS) $(GUI_DESKTOP_OBJS)
	$(CXX) $(CXXFLAGS) $(APP_OBJS) $(GUI_DESKTOP_OBJS) -L$(LIB_DIR) -lbrickgame -o $@ $(GTK_LIBS)

# Build static library
$(STATIC_LIB): $(SNAKE_OBJS) $(TETRIS_OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# Pattern rule for C++ files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Pattern rule for C files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test:
	rm -f test_snake_model
	$(CXX) $(CXXFLAGS) -I $(INCLUDES) test/test_snake_model.cpp brick_game/snake/model/snake_model.cpp -lgtest -lgtest_main -lpthread -o test_snake_model

# Install target
install: all
	@mkdir -p $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET_CLI) $(DESTDIR)$(BINDIR)/
	install -m 755 $(TARGET_DESKTOP) $(DESTDIR)$(BINDIR)/
	@echo "Installed to $(DESTDIR)$(BINDIR)/"

# Uninstall target
uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET_CLI)
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET_DESKTOP)
	@echo "Uninstalled from $(DESTDIR)$(BINDIR)/"

# Distribution package target
dist: clean
	@mkdir -p $(DIST_DIR)
	tar -czf $(DIST_DIR)/brick_game-1.0.tar.gz --exclude=./$(DIST_DIR) --exclude=./$(BUILD_DIR) \
	--exclude=*.o --exclude=*.a --exclude=*.tar.gz --exclude=.git --exclude=*.swp --exclude=*.swo .
	@echo "Distribution package created: $(DIST_DIR)/brick_game-1.0.tar.gz"

dvi:
	@doxygen Doxyfile
	@echo "Documentation created"

# Clean build artifacts
clean:
	rm -rf info/ test_snake_model $(BUILD_DIR) $(TARGET_CLI) $(TARGET_DESKTOP)

# Create necessary directories
$(SNAKE_OBJS): | $(OBJ_DIR)
$(TETRIS_OBJS): | $(OBJ_DIR)
$(APP_OBJS): | $(OBJ_DIR)
$(GUI_CLI_CPP_OBJS): | $(OBJ_DIR)
$(GUI_CLI_C_OBJS): | $(OBJ_DIR)
$(GUI_DESKTOP_OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Phony targets
.PHONY: test all cli desktop clean install uninstall dvi dist
