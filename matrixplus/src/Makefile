NAME=s21_matrix_oop

CXX=g++

CXXFLAGS= -O3 -std=c++17

SOURCEDIR=.
BUILDDIR=obj
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJFILES=$(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: clean $(NAME).a

$(OBJFILES): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

TESTLFLAGS=-lgtest
TESTER=test_$(NAME)
TESTDIR=./test
TESTSRC=$(wildcard $(TESTDIR)/*.cpp)

test: clean
	$(CXX) $(CXXFLAGS) $(SOURCES) $(TESTSRC) -o $(TESTER) $(TESTLFLAGS)
	./$(TESTER)

$(NAME).a: $(OBJFILES)
	ar rc $@ $(OBJFILES)
	ranlib $@

GCOVFILES=*.gcda *.gcno *.html *.css
GCOVFLAGS=-fprofile-arcs -ftest-coverage --coverage
REPORT=report.html

gcov_report:
	$(CXX) $(CXXFLAGS) $(SOURCES) $(TESTSRC) -o $(TESTER) $(TESTLFLAGS) $(GCOVFLAGS)
	./$(TESTER)
	rm -f *-test*.*gcda *-test*.*gcno 
	gcovr -r . --html  -o $(REPORT)

format:
	clang-format -i --style=Google $(SOURCES) $(TESTSRC)

clean:
	rm -rf $(OBJFILES) $(NAME).a $(TESTER) $(GCOVFILES) 

.PHONY: clean all test format
