CXXFLAGS := -std=c++11 -Wall -Wextra

SRCS := pstree.cpp process.cpp
OBJS := $(SRCS:.cpp=.o)

all: pstree

pstree: $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) pstree