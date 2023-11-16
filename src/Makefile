CC=g++
CFLAGS=-Wall -Werror -Wextra
CFLAGS=-Wall -std=c++17 -Wextra -pedantic -g -Werror -fsanitize=address
CCOV=-fprofile-arcs -ftest-coverage
COVFLAGS=$(shell pkg-config --cflags --libs gcovr)
LDFLAGS=-lgcov 
TFLAGS=$(shell pkg-config --libs check)


GCOVR_CFLAGS=-fprofile-arcs -ftest-coverage -fPIC
GCOVR_CFLAGS=--coverage
GCOVR_LFLAGS=-lgcov
GCOVR_LFLAGS=--coverage

GTEST_LFLAGS=-lgtest -lgtest_main 
SANITIZER_LFLAGS=-fsanitize=address

HEADERS=model/calculator/calculator.h
HEADERS+=model/calculator/multiCalculator.h
HEADERS+=model/calculator/singleCalculator.h

HEADERS+=model/credit/creditCalculator.h
HEADERS+=model/deposit/depositCalculator.h
HEADERS+=model/graph/graphCalculator.h
HEADERS+=model/parcer/token.h
HEADERS+=model/parcer/parcer.h
HEADERS+=model/parcer/unaryReplacer.h
HEADERS+=model/parcer/validator.h

HEADERS+=model/rpn/calculatorRpn.h
HEADERS+=model/rpn/flipStack.h
HEADERS+=model/rpn/shuntingYard.h


HEADERS+=controller/controller.h

HEADERS+=protocol/protocol.h


SOURCES=tests/tests_main.cc
SOURCES+=tests/test_calculation.cc
SOURCES+=tests/test_graph.cc
SOURCES+=tests/test_credit.cc
SOURCES+=tests/test_deposit.cc
SOURCES+=tests/test_parcer.cc
SOURCES+=tests/test_validator.cc

SOURCES+=controller/controller.cc
SOURCES+=model/calculator/calculator.cc
SOURCES+=model/calculator/multiCalculator.cc
SOURCES+=model/calculator/singleCalculator.cc

SOURCES+=model/credit/creditCalculator.cc

SOURCES+=model/deposit/depositCalculator.cc

SOURCES+=model/graph/graphCalculator.cc

SOURCES+=model/parcer/parcer.cc
SOURCES+=model/parcer/token.cc
SOURCES+=model/parcer/unaryReplacer.cc
SOURCES+=model/parcer/validator.cc

SOURCES+=model/rpn/calculatorRpn.cc
SOURCES+=model/rpn/flipStack.cc
SOURCES+=model/rpn/shuntingYard.cc

REPORT_DIRECTORY=report

BINARIES=$(patsubst %.cc,%.o,$(SOURCES))


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
	./build/SmartCalc_2_0.app/Contents/MacOS/SmartCalc_2_0

test: run_tests 


run_tests: tests/tests_main.exe
		./tests/tests_main.exe


%.o: %.cc $(HEADERS)
		$(CC) -c $(CFLAGS) $< -o $@ $(GCOVR_CFLAGS) $(GTEST_CFLAGS) 


tests/tests_main.exe: $(BINARIES)
		$(CC) -o $@ $^ $(GTEST_LFLAGS) $(GCOVR_LFLAGS) $(SANITIZER_LFLAGS) -g


EXCLUDE_FROM_COVERAGE=--exclude-lines-by-pattern '.*assert.*' --exclude-throw-branches

gcov_report: run_tests
		mkdir -p $(REPORT_DIRECTORY)
		gcovr . --html --html-details $(EXCLUDE_FROM_COVERAGE) -o $(REPORT_DIRECTORY)/coverage_report.html
		open "" $(REPORT_DIRECTORY)/coverage_report.functions.html  

# check:
# 		cppcheck --enable=all --force *.c SmartCalc.h

REPORT_DIRECTORY=report
VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER=valgrind_report


leaks: tests/tests_main.exe
		leaks --atExit -- ./tests/tests_main.exe


valgrind: tests/tests_main.exe
		mkdir -p $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)
		-valgrind --leak-check=full --show-reachable=no --track-origins=yes --log-file=$(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_report.txt -s ./tests/tests_main.exe > $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
		cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
		cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_report.txt

valgrind_full: tests/tests_main.exe
		mkdir -p $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)
		-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_full_report.txt -s ./tests/tests_main.exe > $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
		cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
		cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_full_report.txt



check_style:
		-clang-format --style=Google -n *.cc
		-clang-format --style=Google -n *.h
		-clang-format --style=Google -n tests/*.cc
		-clang-format --style=Google -n tests/*.h
		-clang-format --style=Google -n model/*.cc
		-clang-format --style=Google -n model/*.h
		-clang-format --style=Google -n view/*.cc
		-clang-format --style=Google -n view/*.h
		-clang-format --style=Google -n controller/*.cc
		-clang-format --style=Google -n controller/*.h

style: style_google

style_google:
		-clang-format --style=Google -i *.cc
		-clang-format --style=Google -i *.h
		-clang-format --style=Google -i tests/*.cc
		-clang-format --style=Google -i tests/*.h
		-clang-format --style=Google -i model/*.cc
		-clang-format --style=Google -i model/*.h
		-clang-format --style=Google -i view/*.cc
		-clang-format --style=Google -i view/*.h
		-clang-format --style=Google -i controller/*.cc
		-clang-format --style=Google -i controller/*.h

style_microsoft:
		-clang-format --style=Microsoft -i *.cc
		-clang-format --style=Microsoft -i *.h
		-clang-format --style=Microsoft -i tests/*.cc
		-clang-format --style=Microsoft -i tests/*.h
		-clang-format --style=Microsoft -i model/*.cc
		-clang-format --style=Microsoft -i model/*.h
		-clang-format --style=Microsoft -i view/*.cc
		-clang-format --style=Microsoft -i view/*.h
		-clang-format --style=Microsoft -i controller/*.cc
		-clang-format --style=Microsoft -i controller/*.h

style_llvm:
		-clang-format --style=LLVM -i *.cc
		-clang-format --style=LLVM -i *.h
		-clang-format --style=LLVM -i tests/*.cc
		-clang-format --style=LLVM -i tests/*.h
		-clang-format --style=LLVM -i model/*.cc
		-clang-format --style=LLVM -i model/*.h
		-clang-format --style=LLVM -i view/*.cc
		-clang-format --style=LLVM -i view/*.h
		-clang-format --style=LLVM -i controller/*.cc
		-clang-format --style=LLVM -i controller/*.h

style_chromium:
		-clang-format --style=Chromium -i *.cc
		-clang-format --style=Chromium -i *.h
		-clang-format --style=Chromium -i tests/*.cc
		-clang-format --style=Chromium -i tests/*.h
		-clang-format --style=Chromium -i model/*.cc
		-clang-format --style=Chromium -i model/*.h
		-clang-format --style=Chromium -i view/*.cc
		-clang-format --style=Chromium -i view/*.h
		-clang-format --style=Chromium -i controller/*.cc
		-clang-format --style=Chromium -i controller/*.h

style_mozilla:
		-clang-format --style=Mozilla -i *.cc
		-clang-format --style=Mozilla -i *.h
		-clang-format --style=Mozilla -i tests/*.cc
		-clang-format --style=Mozilla -i tests/*.h
		-clang-format --style=Mozilla -i model/*.cc
		-clang-format --style=Mozilla -i model/*.h
		-clang-format --style=Mozilla -i view/*.cc
		-clang-format --style=Mozilla -i view/*.h
		-clang-format --style=Mozilla -i controller/*.cc
		-clang-format --style=Mozilla -i controller/*.h

style_webkit:
		-clang-format --style=WebKit -i *.cc
		-clang-format --style=WebKit -i *.h
		-clang-format --style=WebKit -i tests/*.cc
		-clang-format --style=WebKit -i tests/*.h
		-clang-format --style=WebKit -i model/*.cc
		-clang-format --style=WebKit -i model/*.h
		-clang-format --style=WebKit -i view/*.cc
		-clang-format --style=WebKit -i view/*.h
		-clang-format --style=WebKit -i controller/*.cc
		-clang-format --style=WebKit -i controller/*.h





clean:
	rm -rf *.o *.a *.css index.html *.gcno *.gcda *.out *.info test report *.dSYM *.gcov build *.gch SmartCalc_dist SmartCalc_arch.tar.gz tests/*.exe
	rm -rf *.gcda *.gcno tests/*.o tests/*.gcda tests/*.gcno
	rm -rf *.gcda *.gcno model/calculator/*.o model/calculator/*.gcda model/calculator/*.gcno
	rm -rf *.gcda *.gcno model/credit/*.o model/credit/*.gcda model/credit/*.gcno
	rm -rf *.gcda *.gcno model/deposit/*.o model/deposit/*.gcda model/deposit/*.gcno
	rm -rf *.gcda *.gcno model/graph/*.o model/graph/*.gcda model/graph/*.gcno
	rm -rf *.gcda *.gcno model/parcer/*.o model/parcer/*.gcda model/parcer/*.gcno
	rm -rf *.gcda *.gcno model/rpn/*.o model/rpn/*.gcda model/rpn/*.gcno
	rm -rf *.gcda *.gcno controller/*.o controller/*.gcda controller/*.gcno
	rm -rf html
	rm -rf latex
	rm -rf report
	rm -rf doxygen.config.bak
	rm -rf SmartCalc_mac.tar.gz 
	rm -rf $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)
	rm -rf $(REPORT_DIRECTORY)
# rm -rf doxygen.config

rebuild: clean all

.PHONY : dvi clean run test gcov_report install uninstall
