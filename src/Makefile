CC = gcc
FLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17
SRC = file_handler/file_handler.cc \
 	main_class/graph.cc test.cc

clean:
	rm -rf a.out *.dot

build:
	$(CC) $(FLAGS) $(SRC)

test: clean build
	./a.out

debug: clean
	$(CC) $(FLAGS) -g $(SRC)
