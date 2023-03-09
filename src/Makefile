CC = g++
FLAGS = -Wall -Wextra
SRC = main_class/file_handler/file_handler.cc \
 	main_class/graph.cc test.cc algorithms_class/graph_algorithms.cc interface/interface.cc algorithms_class/ant_algorithm/simple_aco.cc

clean:
	rm -rf a.out *.dot

build:
	$(CC) $(FLAGS) $(SRC)

debug:
	c++ -g $(SRC)

test: clean build
	./a.out
