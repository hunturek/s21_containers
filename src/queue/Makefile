CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -Werror
TEST_FILE = "../tests/test_s21_queue.cc"
OS := $(shell uname)

all: gcov_report

gcov_report:
	$(CC) $(CFLAGS) $(TEST_FILE) -o test_queue -lgtest -lgtest_main -lpthread -fprofile-arcs -ftest-coverage
	./test_queue
	gcovr -r . --html --html-details -o coverage_report.html
	rm -f *.gcda *.gcno test_queue
	open coverage_report.html

clean:
	rm -f *.gcda *.gcno test_queue coverage_report.html



