INC_DIR = ./inc
SRC_DIR = ./src
EXEC_SRC_DIR = ./exec_src
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
REQ_DIRS = $(BUILD_DIR) $(OBJ_DIR)

WARNINGS = -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-reserved-id-macro -Wno-implicit-fallthrough -Wno-documentation
OP = -O2
#OP = -g
CC = g++ $(OP) -std=c++17 $(WARNINGS)

INCS = `sdl2-config --cflags` -I$(INC_DIR)
LIBS = `sdl2-config --libs` -lSDL2_image

MKDIR = mkdir -p
EXEC = $(patsubst %, $(BUILD_DIR)/%, $(notdir $(patsubst %.cpp, %, $(wildcard $(EXEC_SRC_DIR)/*.cpp))))
OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(notdir $(patsubst %.cpp, %, $(wildcard $(SRC_DIR)/*.cpp))))

all: $(REQ_DIRS) $(EXEC)

$(REQ_DIRS):
	@$(MKDIR) $@

$(EXEC): $(BUILD_DIR)/%: $(EXEC_SRC_DIR)/%.cpp $(OBJS)
	@echo $@	
	@$(CC) $(INCS) -o $@ $^ $(LIBS)

-include $(OBJS:.o=.d)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo $@
	@$(CC) $(INCS) -MMD -c -o $@ $<

clean:
	-@rm -r $(BUILD_DIR)
