.PHONY: all clean

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET = ../basic_shell.exe
PCH = pch.h
PCH_OUT = pch.h.gch
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(PCH_OUT): $(PCH)
	$(CXX) $(CXXFLAGS) -x c++-header $(PCH) -o $(PCH_OUT)

$(TARGET): $(PCH_OUT) $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) $(PCH_OUT)

