CC = g++
FLAGS = -Wall -Werror -Wextra
SRC = main_class/file_handler/file_handler.cc \
 	main_class/graph.cc test.cc algorithms_class/graph_algorithms.cc interface/interface.cc

clean:
	rm -rf a.out *.dot

build:
	$(CC) $(FLAGS) $(SRC)

test: clean build
	./a.out

debug: clean
	$(CC) $(FLAGS) -g $(SRC)
