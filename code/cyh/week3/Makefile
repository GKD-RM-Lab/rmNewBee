# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -std=c++11 -g

# 定义目标文件和依赖文件
TARGET = robot
SOURCES = main.cpp robot.cpp task.cpp taskscheduler.cpp
HEADERS = robot.hpp task.hpp taskscheduler.hpp
OBJECTS = $(SOURCES:.cpp=.o)

# 默认规则
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# 生成目标文件
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
