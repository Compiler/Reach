

CXX = g++
C++_VERSION = c++17
CXXFLAGS = -std=$(C++_VERSION) -Wall -w -g

OUT_DIR = bin
LAUNCHER_NAME = Reach
SRC_DIR = src
ENTRY_POINT = src/main.cpp

#Libs
GLAD_ROOT = outsourced/glad/
GLAD_INC = $(GLAD_ROOT)include
GLAD_SRC = $(GLAD_ROOT)src
GLFW_ROOT = outsourced/glfw-3.3.2/MinGWmingw32/
GLFW_INC = $(GLFW_ROOT)include
GLFW_LIB = $(GLFW_ROOT)lib
GLFW_SRC = $(GLFW_ROOT)../src
STBIMAGE_ROOT = outsourced/stbimage
GLM_ROOT = outsourced/glm/

INC_INTERNAL = -I $(SRC_DIR)
INC=-I $(SRC_DIR)  -I $(GLAD_INC) -I $(GLFW_INC) -I $(GLM_ROOT) -I $(STBIMAGE_ROOT)
LIBS = -L $(GLFW_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32

OUT_DIR = bin
OBJ =
RENDERING_OBJS = Window.o
REACH_OBJS = ReachCore.o


OUT_OBJECTS = $(patsubst %.o, $(OUT_DIR)/%.o, $(RENDERING_OBJS) $(OBJ) $(REACH_OBJS))
ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) $(INC_INTERNAL)

all: main

main: $(REACH_OBJS) 
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(ENTRY_POINT) $(REACH_OBJS) $(GLAD_SRC)/glad.c $(LINKS)

ReachCore.o: 
	$(ALL_SETTINGS) -o  $(OBJ) 

$(OBJ): %.o: src/%.cpp
	$(ALL_SETTINGS) -c -o $(OUT_DIR)/$@ $< 

$(RENDERING_OBJS): %.o: src/Reach/Rendering/%.cpp
	$(ALL_SETTINGS) -c -o $(OUT_DIR)/$@ $< 

$(REACH_OBJS): %.o: src/Reach/%.cpp
	$(ALL_SETTINGS) -c -o $(OUT_DIR)/$@ $< 



run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe

launch:
	make
	make run