CXX = g++
C++_VERSION = c++17
CXXFLAGS = -std=$(C++_VERSION) -Wall -w -g -static-libgcc -static-libstdc++

OUT_DIR = bin
LAUNCHER_NAME = Sanbox
SRC_DIR = src
ENTRY_POINT = src/main.cpp

#Libs
GLAD_ROOT = ../outsourced/glad/
GLAD_INC = $(GLAD_ROOT)include
GLAD_SRC = $(GLAD_ROOT)src

GLFW_ROOT = ../outsourced/glfw-3.3.2/MinGWmingw32/
GLFW_INC = $(GLFW_ROOT)include
GLFW_LIB = $(GLFW_ROOT)lib
GLFW_SRC = $(GLFW_ROOT)../src

STBIMAGE_ROOT = ../outsourced/stbimage
GLM_ROOT = ../outsourced/glm/
ENTT_ROOT = ../outsourced/entt
ENTT_SRC = $(ENTT_ROOT)

REACH_INC = ../src/
REACH_CORE = ..
REACH_LIB = outsourced/

INC= -I $(REACH_INC)  -I $(GLAD_INC) -I $(GLFW_INC) -I $(GLM_ROOT) -I $(STBIMAGE_ROOT) -I $(ENTT_SRC) -I $(IMGUI_SRC) #-I $(BOX2D_INC)
LIBS = -L$(GLFW_LIB) -L$(REACH_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32 -lreachengine

all: main


main: $(ENTRY_POINT)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $< $(GLAD_SRC)/glad.c $(LINKS)