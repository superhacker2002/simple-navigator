CC =gcc
FLAGS =-Wall -Werror -Wextra -std=c++17
GTEST_FLAG =-lgtest
LINKER_FLAGS =-lstdc++
TEST_FLAGS =$(FLAGS) $(LINKER_FLAGS) $(GTEST_FLAG)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LINKER_FLAGS +=-lm -lpthread
endif

SRC_GRAPH = graph/file_handler/file_handler.cc \
			graph/graph.cc \

SRC_ALGORITHMS = algorithms/graph_algorithms.cc \
				algorithms/ant_algorithm/simple_aco.cc 

SRC_GRAPH_TEST = tests/graph_tests.cc
SRC_ALGORITHMS_TEST = tests/algorithms_tests.cc

GRAPH_LIB = s21_graph.a
ALGORITHMS_LIB = s21_graph_algorithms.a

GRAPH_OBJ = $(patsubst %.cc, %.o, $(SRC_GRAPH))
ALGORITHMS_OBJ = $(patsubst %.cc, %.o, $(SRC_ALGORITHMS))


all: s21_graph.a clean

%.o: %.cc
	@$(CC) -c $< -o $@ $(FLAGS)

$(GRAPH_LIB): $(GRAPH_OBJ)
	ar -rcs $(GRAPH_LIB) $?

$(ALGORITHMS_LIB): $(GRAPH_OBJ) $(ALGORITHMS_OBJ)
	ar -rcs $(ALGORITHMS_LIB) $?

test: $(GRAPH_LIB) $(ALGORITHMS_LIB)
	@$(CC) $(SRC_GRAPH_TEST) $(GRAPH_LIB) -o graph_tests $(TEST_FLAGS)
	@$(CC) $(SRC_ALGORITHMS_TEST) $(ALGORITHMS_LIB) -o algorithms_tests $(TEST_FLAGS)
	./graph_tests
	./algorithms_tests

clean:
	rm -rf a.out *.dot a.out* $(GRAPH_OBJ) $(ALGORITHMS_OBJ) graph_tests algorithms_tests

fclean: clean
	rm -rf $(GRAPH_LIB) $(ALGORITHMS_LIB)

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

