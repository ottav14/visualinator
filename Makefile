
# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11
LIBS = -lSDL2 -lm -lQt5Core -lQt5Widgets -lQt5Gui -lstdc++
INCLUDES = -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtWidgets

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = bin

# Main target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# Target to build and run the application
run: $(TARGET)
	./$(TARGET)
