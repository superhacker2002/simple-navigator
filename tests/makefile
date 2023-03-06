CC = gcc
FLAGS = -Wall -Werror -Wextra -lgtest -lm -lpthread -lstdc++ -std=c++17 -g
SRC = ../src/main_class/file_handler/file_handler.cc \
 	../src/main_class/graph.cc \
	../src/algorithms_class/graph_algorithms.cc \
	algorithms_tests.cc \
	../src/algorithms_class/ant_algorithms/simple_aco.cc

clean:
	rm -rf a.out *.dot a.out*

build:
	$(CC) $(SRC) $(FLAGS)

test: clean build
	./a.out --gtest_repeat=100 --gtest_break_on_failure
	make clean

debug: clean
	$(CC) $(FLAGS) -g $(SRC)
