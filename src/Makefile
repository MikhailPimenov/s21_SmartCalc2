CC=g++
CFLAGS=-Wall -Werror -Wextra
CFLAGS=-Wall -std=c++17 -Wextra -pedantic -g -Werror
CCOV=-fprofile-arcs -ftest-coverage
COVFLAGS=$(shell pkg-config --cflags --libs gcovr)
LDFLAGS = -lgcov
TFLAGS=$(shell pkg-config --libs check)


GCOVR_CFLAGS=-fprofile-arcs -ftest-coverage -fPIC
GCOVR_CFLAGS=--coverage
GCOVR_LFLAGS=-lgcov
GCOVR_LFLAGS=--coverage

GTEST_LFLAGS=-lgtest -lgtest_main

HEADERS=model/SmartCalc.h

SOURCES=tests/tests_main.cc
SOURCES+=tests/test.cc
SOURCES+=model/model.cc
SOURCES+=model/bonus_model.cc

REPORT_DIRECTORY=report

BINARIES=$(patsubst %.c,%.o,$(SOURCES))


all: install run	

install:
	sh install_script.sh

uninstall:
	rm -rf build

dvi:
	doxygen doxygen.config
	open html/index.html
# doxygen -g doxygen.config

dist:
	sh dist_script.sh

run:
	./build/SmartCalc_1_0.app/Contents/MacOS/SmartCalc_1_0

test: run_tests 


run_tests: tests/tests_main.exe
		./tests/tests_main.exe


%.o: %.cc $(HEADERS)
		$(CC) -c $(CFLAGS) $< -o $@ $(GCOVR_CFLAGS) $(GTEST_CFLAGS)



tests/tests_main.exe: $(BINARIES)
		$(CC) -o $@ $^ $(GTEST_LFLAGS) $(GCOVR_LFLAGS) -g


EXCLUDE_FROM_COVERAGE=--exclude-lines-by-pattern '.*assert.*' --exclude-throw-branches

gcov_report: run_tests
		mkdir -p $(REPORT_DIRECTORY)
		gcovr . --html --html-details $(EXCLUDE_FROM_COVERAGE) -o $(REPORT_DIRECTORY)/coverage_report.html
		open "" $(REPORT_DIRECTORY)/coverage_report.functions.html  

check:
	cppcheck --enable=all --force *.c SmartCalc.h

leakscheck: test
	leaks --atExit -- ./test
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test


clean:
	rm -rf *.o *.a *.css index.html *.gcno *.gcda *.out *.info test report *.dSYM *.gcov build *.gch SmartCalc_dist SmartCalc_arch.tar.gz tests/*.exe
	rm -rf *.gcda *.gcno tests/*.o tests/*.gcda tests/*.gcno
	rm -rf *.gcda *.gcno model/*.o model/*.gcda model/*.gcno
	rm -rf html
	rm -rf latex
	rm -rf report
	rm -rf doxygen.config.bak
# rm -rf doxygen.config

rebuild: clean all

.PHONY : dvi clean run test gcov_report install uninstall
