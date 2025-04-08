#talgov44@gmail.com

CXX = clang++
CXXFLAGS = -Wall -g -std=c++11 -lstdc++
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SRCS = Algorithms/Algorithms.cpp Graph/graph.cpp Structures/PriorityQueue.cpp Structures/Queue.cpp Structures/UnionFind.cpp
# OBJS = $(SRCS:.cpp=.o)
MAIN_SRC = main.cpp
TEST_SRC = TestMain.cpp Test.cpp

Test: test
	./test
#	./$^

all: main test

# main: main.o $(OBJS)
main: main.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(SRCS) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

valgrind: main_build test_build
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./main_build 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test_build 2>&1 | { egrep "lost| at " || true; }

clean:
	rm -f $(OBJS) main_build test_build TestMain.o Test.o


.PHONY: all clean valgrind Test