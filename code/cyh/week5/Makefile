# Makefile for demo1 and demo2 client programs

# Compiler settings
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++11
LDFLAGS  := 

# Targets
TARGETS :=  client server

# Source files

SRC_CLIENT := client.cpp
SRC_SERVER := server.cpp

# Header files
HEADERS := order.h

# Default target (build all)
all: $(TARGETS)

client: $(SRC_CLIENT) $(HEADERS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

server: $(SRC_SERVER) $(HEADERS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
# Clean up
clean:
	rm -f $(TARGETS)

.PHONY: all clean