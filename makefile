INC_DIR = ./inc
SRC_DIR = ./src
EXEC_SRC_DIR = ./exec_src
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
REQ_DIRS = $(BUILD_DIR) $(OBJ_DIR)

WARNINGS = -Weverything -Wno-c++98-compat -Wno-padded
CC = g++ -std=c++17 $(WARNINGS)

MKDIR = mkdir -p
EXEC_NAMES = run
EXEC = $(patsubst %, $(BUILD_DIR)/%, $(notdir $(patsubst %.cpp, %, $(EXEC_NAMES))))
OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(notdir $(patsubst %.cpp, %, $(wildcard $(SRC_DIR)/*.cpp))))
DEPS = $(patsubst %.o, %.d, $(OBJS))

all: $(REQ_DIRS) $(EXEC)

$(REQ_DIRS):
	@$(MKDIR) $@

$(EXEC): $(BUILD_DIR)/%: $(EXEC_SRC_DIR)/%.cpp $(OBJS)
	@echo $@	
	-@$(CC) -o $@ $^ -I$(INC_DIR) $(LIBS)

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo $@
	@$(CC) -MMD -c -o $@ $< -I$(INC_DIR)

clean:
	-@rm -r $(BUILD_DIR)
