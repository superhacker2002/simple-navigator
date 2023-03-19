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
				algorithms/salesman_solver/brute_force_algorithm/brute_force.cc \
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

debug_test_algorithms: $(ALGORITHMS_LIB)
	@$(CC) $(SRC_ALGORITHMS_TEST) $(ALGORITHMS_LIB) -o algorithms_tests $(TEST_FLAGS) -g

clean:
	rm -rf a.out *.dSYM a.out* $(GRAPH_OBJ) $(ALGORITHMS_OBJ) graph_tests algorithms_tests console_interface

fclean: clean
	rm -rf $(GRAPH_LIB) $(ALGORITHMS_LIB) *.dot

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n $(SRC_GRAPH) $(SRC_ALGORITHMS) \
					$(SRC_INTERFACE) $(SRC_GRAPH_TEST) \
					$(SRC_ALGORITHMS_TEST) s21_graph.h \
					s21_graph_algorithms.h interface/*.h \
					helpers/*.h helpers/containers/*.h \
					graph/*.h graph/iterators/*.h \
					graph/file_handler/*.h \
					algorithms/*.h algorithms/salesman_solver/*.h \
					algorithms/salesman_solver/ant_algorithm/*.h \
					algorithms/salesman_solver/branch_and_bound_algorithm/*.h \
					algorithms/salesman_solver/brute_force_algorithm/*.h
	rm -rf .clang-format

