# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g

# Directories
SRC_DIR = src
INCLUDE_DIR = include
APP_DIR = app
OBJ_DIR = obj

# Create obj directories if they don't exist
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(OBJ_DIR)/process)
$(shell mkdir -p $(OBJ_DIR)/expression)
$(shell mkdir -p $(OBJ_DIR)/queue)
$(shell mkdir -p $(OBJ_DIR)/system)

# Include paths
INCLUDES = -I$(INCLUDE_DIR)

# Find all source files
PROCESS_SRCS = $(wildcard $(SRC_DIR)/process/*.cpp)
EXPRESSION_SRCS = $(wildcard $(SRC_DIR)/expression/*.cpp)
QUEUE_SRCS = $(wildcard $(SRC_DIR)/queue/*.cpp)
SYSTEM_SRCS = $(wildcard $(SRC_DIR)/system/*.cpp)
APP_SRCS = $(wildcard $(APP_DIR)/*.cpp)

# Generate object file names
PROCESS_OBJS = $(patsubst $(SRC_DIR)/process/%.cpp,$(OBJ_DIR)/process/%.o,$(PROCESS_SRCS))
EXPRESSION_OBJS = $(patsubst $(SRC_DIR)/expression/%.cpp,$(OBJ_DIR)/expression/%.o,$(EXPRESSION_SRCS))
QUEUE_OBJS = $(patsubst $(SRC_DIR)/queue/%.cpp,$(OBJ_DIR)/queue/%.o,$(QUEUE_SRCS))
SYSTEM_OBJS = $(patsubst $(SRC_DIR)/system/%.cpp,$(OBJ_DIR)/system/%.o,$(SYSTEM_SRCS))
APP_OBJS = $(patsubst $(APP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(APP_SRCS))

# All object files
OBJS = $(PROCESS_OBJS) $(EXPRESSION_OBJS) $(QUEUE_OBJS) $(SYSTEM_OBJS) $(APP_OBJS)

# Output executable
TARGET = process_pool

# Default target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)
	@echo "Build complete: $(TARGET)"

# Compilation rules for different directories
$(OBJ_DIR)/process/%.o: $(SRC_DIR)/process/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/expression/%.o: $(SRC_DIR)/expression/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/queue/%.o: $(SRC_DIR)/queue/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/system/%.o: $(SRC_DIR)/system/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(APP_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*/*.o $(TARGET)
	@echo "Clean complete"

# Phony targets
.PHONY: all clean

# Dependencies
-include $(OBJS:.o=.d)

# Generate dependency files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(OBJ_DIR)/%.d: $(APP_DIR)/%.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

