CC =gcc
FLAGS =-Wall -Werror -Wextra -std=c++17
GTEST_FLAG =-lgtest
LINKER_FLAGS =-lstdc++

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LINKER_FLAGS +=-lm -lpthread
endif

TEST_FLAGS =$(FLAGS) $(GTEST_FLAG) $(LINKER_FLAGS)

SRC_GRAPH = graph/file_handler/file_handler.cc \
			graph/graph.cc \

SRC_ALGORITHMS = algorithms/graph_algorithms.cc \
				algorithms/salesman_solver/ant_algorithm/simple_aco.cc  \
				algorithms/salesman_solver/branch_and_bound_algorithm/branch_and_bound.cc \
				algorithms/salesman_solver/solver_factory.cc

SRC_INTERFACE = main.cc interface/interface.cc

SRC_GRAPH_TEST = tests/graph_tests.cc
SRC_ALGORITHMS_TEST = tests/algorithms_tests.cc

GRAPH_LIB = s21_graph.a
ALGORITHMS_LIB = s21_graph_algorithms.a

GRAPH_OBJ = $(patsubst %.cc, %.o, $(SRC_GRAPH))
ALGORITHMS_OBJ = $(patsubst %.cc, %.o, $(SRC_ALGORITHMS))

.PHONY: all s21_graph.a s21_graph_algorithms.a interface test clean fclean style_check

all: $(GRAPH_LIB) clean

%.o: %.cc
	@$(CC) -c $< -o $@ $(FLAGS)

$(GRAPH_LIB): $(GRAPH_OBJ)
	ar -rcs $(GRAPH_LIB) $?

$(ALGORITHMS_LIB): $(GRAPH_OBJ) $(ALGORITHMS_OBJ)
	ar -rcs $(ALGORITHMS_LIB) $?

interface: $(ALGORITHMS_LIB)
	@$(CC) $(SRC_INTERFACE) $(ALGORITHMS_LIB) -o console_interface $(FLAGS) $(LINKER_FLAGS)
	./console_interface

test: test_graph test_algorithms

test_graph: $(GRAPH_LIB)
	@$(CC) $(SRC_GRAPH_TEST) $(GRAPH_LIB) -o graph_tests $(TEST_FLAGS)
	./graph_tests

test_algorithms: $(ALGORITHMS_LIB)
	@$(CC) $(SRC_ALGORITHMS_TEST) $(ALGORITHMS_LIB) -o algorithms_tests $(TEST_FLAGS)
	./algorithms_tests

clean:
	rm -rf a.out *.dSYM *.dot a.out* $(GRAPH_OBJ) $(ALGORITHMS_OBJ) graph_tests algorithms_tests console_interface

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

