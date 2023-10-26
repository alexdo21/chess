# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall

# Source files
SRCS = Main.cpp BoardUtils.cpp Bitboard.cpp Game.cpp

# Header files
HDRS = Constants.h BoardUtils.h Bitboard.h Game.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = chess.exe

# Debug executable name
DEBUG_EXEC = chess_debug.exe

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Build the debug executable
debug: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(OBJS) -o $(DEBUG_EXEC)

# Build object files from files from source files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(EXEC) $(DEBUG_EXEC)

.PHONY: all debug clean
