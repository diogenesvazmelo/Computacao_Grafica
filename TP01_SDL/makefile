CXX 			:= g++
CXXFLAGS 	:= -std=c++1z -lSDL2 -lSDL2_image -lSOIL -lglut -lGLEW -lGLU -lGL
LDFLAGS  	:= -L/usr/lib -lstdc++ -lm
OBJ_DIR 	:= ./obj
APP_DIR		:= ./bin
TARGET		:= game
INCLUDE 	:= ./include
SRC 			:= 							\
	$(wildcard ./*.cpp) 		\
	$(wildcard ./src/*.cpp) \

OBJECTS		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) -o $(APP_DIR)/$(TARGET) $^ $(CXXFLAGS)
 
.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -game
debug: all

release: CXXFLAGS += -02
release: all

clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -rvf $(APP_DIR)
