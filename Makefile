CXX = g++
# CXXFLAGS = -Wall -O3 -DDEBUG
CXXFLAGS = -Wall -O3 
LDFLAGS = -lboost_graph
RM = gio trash -f

TARGETS = bvd_demo

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

bvd_demo: bvd_demo.o 
	-$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)


demo: bvd_demo
	-./bvd_demo

clean:
	-$(RM) $(OBJS) $(TARGETS)

