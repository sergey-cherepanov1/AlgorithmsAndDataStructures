CXX = g++
CXXFLAGS = -std=c++11 -Werror -Wpedantic -Wall
TARGET = ascii85
TEST_TARGET = test

SRCS = $(wildcard *.cpp)
TESTS = $(wildcard test_*.cpp)

OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TESTS:.cpp=.o)

all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(filter-out main.o,$(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgtest_main -pthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
