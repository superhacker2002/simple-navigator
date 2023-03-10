CC = gcc 
FLAGS = -Wall -Werror -Wextra -lgtest -lstdc++ -std=c++17 -g
SRC = src/main_class/file_handler/file_handler.cc \
 	src/main_class/graph.cc \
	src/algorithms_class/graph_algorithms.cc \
	src/algorithms_class/ant_algorithm/simple_aco.cc \
	test.cc

clean:
	rm -rf a.out *.dot a.out*

build:
	$(CC) $(SRC) src/interface/interface.cc $(FLAGS)

tests: clean build
	./a.out

debug: clean
	$(CC) $(FLAGS) -g $(SRC)

style_check:
	cp materials/linters/.clang-format .
	clang-format -i tests/*.cc \
					src/algorithms_class/*.h \
					src/algorithms_class/*.cc \
					src/algorithms_class/ant_algorithm/*.h \
					src/algorithms_class/ant_algorithm/*.cc \
					src/helpers/containers/*.h \
					src/helpers/*.h \
					src/main_class/file_handler/*.cc \
					src/main_class/file_handler/*.h \
					src/main_class/iterators/*.h \
					src/main_class/*.cc \
					src/main_class/*.h
	rm -rf .clang-format

