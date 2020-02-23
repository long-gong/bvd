CXX = g++
# CXXFLAGS = -Wall -O3 -DDEBUG
CXXFLAGS = -Wall -O3  
LDFLAGS = -lboost_graph 
RM = gio trash -f

TARGETS = bvd_demo doubly_stochastic_example

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

bvd_demo: bvd_demo.o 
	-$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

doubly_stochastic_example: doubly_stochastic_example.o 
	-$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

demo: bvd_demo
	-./bvd_demo

example: doubly_stochastic_example
	-./doubly_stochastic_example

clean:
	-$(RM) $(OBJS) $(TARGETS)

