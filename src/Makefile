CC=g++
CFLAGS=-Wall -Werror -Wextra
CFLAGS=-Wall -std=c++17 -Wextra -pedantic -g -Werror
# STRICT_CFLAGS=-Wall -std=c++17 -Wextra -pedantic -g -Werror
CCOV = -fprofile-arcs -ftest-coverage
SOURSE_FILE = *.c SmartCalc.h
# COVFLAGS = --coverage
COVFLAGS=$(shell pkg-config --cflags --libs gcovr)
LDFLAGS = -lgcov
# TFLAGS = -lcheck -lm -lsubunit
TFLAGS=$(shell pkg-config --libs check)
#ASAN = -g -fsanitize=address


GCOVR_CFLAGS=-fprofile-arcs -ftest-coverage -fPIC
GCOVR_CFLAGS=--coverage
GCOVR_LFLAGS=-lgcov
GCOVR_LFLAGS=--coverage

GTEST_LFLAGS=-lgtest -lgtest_main

HEADERS=SmartCalc.h

SOURCES=tests_main.c
SOURCES+=test.c
SOURCES+=stack.c
SOURCES+=shunting_yard.c
SOURCES+=parcer.c
SOURCES+=calc_rpn.c
SOURCES+=bonus_part.c


BINARIES=$(patsubst %.c,%.o,$(SOURSE_FILE))

azaza:
	$(wildcard SOURSE_FILE)

all: clean install run	

install:
	sh install_script.sh

uninstall:
	rm -rf build

dvi:
	open ../README.md

dist:
	sh dist_script.sh

run:
	./build/SmartCalc_1_0.app/Contents/MacOS/SmartCalc_1_0

# test: 
# 	$(CC) $(CFLAGS) $(ASAN) $(CCOV) $(SOURSE_FILE) -o test $(TFLAGS)
# 	-./test

test: run_tests gcov_report

run_tests: tests/tests_main.exe
		./tests/tests_main.exe


%.o: %.cc $(HEADERS)
		$(CC) -c $(CFLAGS) $< -o $@ $(GCOVR_CFLAGS) $(GTEST_CFLAGS)



tests/tests_main.exe: $(BINARIES)
		$(CC) -o $@ $^ $(GTEST_LFLAGS) $(GCOVR_LFLAGS) -g

gcov_report: run_tests
	$(CC) $(ASAN) $(GFLAGS) $(CCOV) $(SOURSE_FILE) $(TFLAGS) -o ./htmlreport.out
	./htmlreport.out
	lcov -t "htmlreport" -o test.info -c -d .
	genhtml -o report test.info
# gcovr . --html --html-details -o $(REPORT_DIRECTORY)/coverage_report.html
# open $(REPORT_DIRECTORY)/index.html

check:
	cppcheck --enable=all --force *.c SmartCalc.h

leakscheck: test
	leaks --atExit -- ./test
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test


clean:
	rm -rf *.o *.a *.css index.html *.gcno *.gcda *.out *.info test report *.dSYM *.gcov build *.gch SmartCalc_dist SmartCalc_arch.tar.gz tests/*.exe

rebuild: clean all

.PHONY : dvi clean run test gcov_report install uninstall