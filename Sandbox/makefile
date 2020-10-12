CXX = g++
C++_VERSION = c++17
CXXFLAGS = -std=$(C++_VERSION) -Wall -w -g -static-libgcc -static-libstdc++

OUT_DIR = bin
LAUNCHER_NAME = Sandbox.exe
SRC_DIR = src
ENTRY_POINT = $(SRC_DIR)/main.cpp

#Libs
GLAD_ROOT = ../ReachEngine/outsourced/glad/
GLAD_INC = $(GLAD_ROOT)include
GLAD_SRC = $(GLAD_ROOT)src

GLFW_ROOT = ../ReachEngine/outsourced/glfw-3.3.2/MinGWmingw32/
GLFW_INC = $(GLFW_ROOT)include
GLFW_LIB = $(GLFW_ROOT)lib
GLFW_SRC = $(GLFW_ROOT)../src

STBIMAGE_ROOT = ../ReachEngine/outsourced/stbimage
GLM_ROOT = ../ReachEngine/outsourced/glm/
ENTT_ROOT = ../ReachEngine/outsourced/entt
ENTT_SRC = $(ENTT_ROOT)
STBIMAGE_ROOT = outsourced/stbimage
IMGUI_ROOT = outsourced/imgui
IMGUI_SRC = $(IMGUI_ROOT)/

REACH_INC = ../ReachEngine/src
REACH_CORE = ..
REACH_LIB = ../ReachEngine/bin

INC= -I $(REACH_INC) -I $(GLAD_INC) -I $(GLFW_INC) -I $(GLM_ROOT) -I $(STBIMAGE_ROOT) -I $(ENTT_SRC) -I $(IMGUI_SRC) #-I $(BOX2D_INC)
LIBS = -L$(GLFW_LIB) -L$(REACH_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32 -lreachengine
ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) 

all: main


main: $(ENTRY_POINT)
	$(ALL_SETTINGS) $(ENTRY_POINT) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(GLAD_SRC)/glad.c $(LINKS)


trial:$(ENTRY_POINT)
	$(ALL_SETTINGS) src/main.cpp -o out $(LINKS)