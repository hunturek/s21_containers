CC = g++
CFLAGS = -Wall -Wextra -Werror -lstdc++ -lm
TEST_FLAGS = -lgtest -pthread

all: test

test: clean test_s21_map.cc
	$(CC) $(CFLAGS) test_s21_map.cc -o test $(TEST_FLAGS)
	./test

clean:
	rm -rf test
