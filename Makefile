#talgov44@gmail.com
SRCS = main.cpp \
       ../Graph/graph.cpp \
       ../Graph/Node.cpp \
       ../Algorithms/Algorithms.cpp \
       ../Structures/Queue.cpp \
       ../Structures/UnionFind.cpp \
       ../Structures/PriorityQueue.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -std=c++11

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o main


test: $(OBJS)
	# כאן תוכל להוסיף את הפקודות להרצת הבדיקות (הנחתי שאין לך כרגע קובץ טסטים)

valgrind: main
	valgrind --leak-check=full ./main

clean:
	rm -f $(OBJS) main

.PHONY: clean valgrind test main.o