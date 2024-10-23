NAME:=brick_game_v1

CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
LFLAGS:=-lncurses

BUILDDIR:=./build
EXECUTABLE:=$(BUILDDIR)/$(NAME)

LIBDIR:=./brick_game/tetris
LIBSOURCE:=$(LIBDIR)/backend.c $(LIBDIR)/connect.c $(LIBDIR)/fsm.c

GUIDIR:=./gui/cli
GUISOURCE:=$(GUIDIR)/frontend.c

RUNDIR:=./run
RUNSOURCE:=$(RUNDIR)/main.c

SOURCE:=$(LIBSOURCE) $(GUISOURCE) $(RUNSOURCE)

OBJLIB:= $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(LIBSOURCE))
OBJGUI:= $(patsubst $(GUIDIR)/%.c,$(BUILDDIR)/%.o,$(GUISOURCE))
OBJRUN:= $(patsubst $(RUNDIR)/%.c,$(BUILDDIR)/%.o,$(RUNSOURCE))
OBJ:=$(OBJLIB) $(OBJGUI) $(OBJRUN) 

all: $(EXECUTABLE)

mk_build:
	mkdir -p $(BUILDDIR)

$(OBJLIB): $(BUILDDIR)/%.o : $(LIBDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
$(OBJGUI): $(BUILDDIR)/%.o : $(GUIDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
$(OBJRUN): $(BUILDDIR)/%.o : $(RUNDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(EXECUTABLE): mk_build $(OBJLIB) $(OBJGUI) $(OBJRUN) 
	$(CC) $(OBJ) -o $@ $(LFLAGS)

install: all
	install $(EXECUTABLE) $(NAME)

uninstall:
	rm -f $(NAME)

dvi:
	doxygen Doxyfile

ARCH:=$(NAME).tar.gz
dist:
	tar -czf $(ARCH) $(SOURCE)

TST_SOURCE:=test/*.c
TESTER:=test_brick_game_v1
TST_LFLAGS:=-pthread -lcheck -lrt -lm -lsubunit
test: clean
	$(CC) $(CFLAGS) $(TST_SOURCE) $(LIBSOURCE) -o $(TESTER) $(TST_LFLAGS) -g
	./$(TESTER)

GCOV_LFLAGS:=-fprofile-arcs -ftest-coverage --coverage 
REPORT:=report.html
gcov_report: clean
	$(CC) $(TST_SOURCE) $(LIBSOURCE) -o $(TESTER) $(GCOV_LFLAGS) $(TST_LFLAGS) -g
	./$(TESTER)
	gcovr -r . --html --html-details  -o $(REPORT)
	rm -f test*test*.gcda test*test*.gcno
	firefox $(REPORT)

format:
	clang-format -i --style=Google $(LIBSOURCE) $(GUISOURCE) $(RUNSOURCE) $(TST_SOURCE)

clean:
	rm -rf $(BUILDDIR)/* docs $(ARCH) $(TESTER) *.gcda *.gcno *.html *.css $(REPORT) test/logs/*

.PHONY: all install uninstall clean dvi dist test
