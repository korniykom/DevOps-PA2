CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

TARGET = trig_program

SRCS = main.cpp TrigFunction.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

