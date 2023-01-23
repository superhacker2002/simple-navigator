CC=g++
FLAGS=-Wall -Werror -Wextra
SRC=FileHandler/FileHandler.cc MainClass/Graph.cc test.cc

clean:
	rm -rf a.out


build:
	$(CC) $(FLAGS) $(SRC)


test: clean build
	./a.out


debug: clean
	$(CC) $(FLAGS) -g $(SRC)
