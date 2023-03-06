CC = gcc 
FLAGS = -Wall -Werror -Wextra -lgtest -lstdc++ -std=c++17 -g
SRC = ../../main_class/graph.cc tests.cc simple_aco.cc ../../main_class/file_handler/file_handler.cc

clean:
	rm -rf a.out *.dot a.out*

build:
	$(CC) $(SRC) $(FLAGS)

tests: clean build
	./a.out
