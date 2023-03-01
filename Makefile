CC = gcc 
FLAGS = -Wall -Werror -Wextra -lgtest -lstdc++ -std=c++17 -g
SRC = src/main_class/file_handler/file_handler.cc \
 	src/main_class/graph.cc \
	src/algorithms_class/graph_algorithms.cc \
	algorithms_tests.cc

clean:
	rm -rf a.out *.dot a.out*

build:
	$(CC) $(SRC) $(FLAGS)

tests: clean build
	./a.out

debug: clean
	$(CC) $(FLAGS) -g $(SRC)

style_check:
	cp materials/linters/.clang-format .
	clang-format -n tests/* \
					src/algorithms_class/* \
					src/helpers/containers/* \
					src/helpers/*.h \
					src/main_class/file_handler/* \
					src/main_class/iterators/* \
					src/main_class/*.cc \
					src/main_class/*.h
	rm -rf .clang-format

