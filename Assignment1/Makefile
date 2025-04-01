CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall
TARGET = ascii85
TEST_TARGET = test
OBJDIR = obj

MAIN_SRCS = $(filter-out tests.cpp, $(wildcard *.cpp))
TEST_SRC = tests.cpp

MAIN_OBJS = $(MAIN_SRCS:%.cpp=$(OBJDIR)/%.o)
TEST_OBJ = $(TEST_SRC:%.cpp=$(OBJDIR)/%.o)

TEST_DEPS = $(filter-out $(OBJDIR)/main.o, $(MAIN_OBJS))

.PHONY: all test clean

all: $(OBJDIR) $(TARGET)

$(TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_DEPS) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgtest_main -pthread

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_TARGET)
