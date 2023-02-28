CC = g++ 
FLAGS = -lgtest -std=c++17
SRC = ../src/main_class/file_handler/file_handler.cc \
 	../src/main_class/graph.cc \
	../src/algorithms_class/graph_algorithms.cc \
	graph_tests.cc

clean:
	rm -rf a.out *.dot

build:
	$(CC) $(FLAGS) $(SRC)

test: clean build
	./a.out

debug: clean
	$(CC) $(FLAGS) -g $(SRC)
