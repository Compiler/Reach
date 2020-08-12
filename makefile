

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



OBJECTS = $(OUT_DIR)/ReachCore.o $(OUT_DIR)/FileLoaderFactory.o $(OUT_DIR)/SceneManager.o $(OUT_DIR)/Scene.o $(OUT_DIR)/InputManager.o $(OUT_DIR)/Window.o 
 
all: main

main: $(ENTRY_POINT) ReachCore.o 
	$(CXX) $(CXXFLAGS) $(LIBS) $(INC) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(OBJECTS) $(ENTRY_POINT) $(GLAD_SRC)/glad.c $(LINKS)


ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) $(INC_INTERNAL)

ReachCore.o: $(SRC_DIR)/Reach/ReachCore.cpp FileLoaderFactory.o SceneManager.o Scene.o InputManager.o Window.o
	$(ALL_SETTINGS) -c $(SRC_DIR)/Reach/ReachCore.cpp -o $(OUT_DIR)/ReachCore.o 

InputManager.o: $(SRC_DIR)/Reach/Tools/Input/InputManager.cpp 
	$(ALL_SETTINGS) -c $(SRC_DIR)/Reach/Tools/Input/InputManager.cpp -o $(OUT_DIR)/InputManager.o 

Scene.o: $(SRC_DIR)/Reach/Tools/Scenes/Scene.cpp 
	$(ALL_SETTINGS) -c $(SRC_DIR)/Reach/Tools/Scenes/Scene.cpp -o $(OUT_DIR)/Scene.o 

SceneManager.o: $(SRC_DIR)/Reach/Tools/Scenes/SceneManager.cpp 
	$(ALL_SETTINGS) -c $(SRC_DIR)/Reach/Tools/Scenes/SceneManager.cpp -o $(OUT_DIR)/SceneManager.o 

FileLoaderFactory.o: $(SRC_DIR)/Reach/Tools/Files/FileLoaderFactory.cpp 
	$(ALL_SETTINGS) -c $(SRC_DIR)/Reach/Tools/Files/FileLoaderFactory.cpp -o $(OUT_DIR)/FileLoaderFactory.o 

Window.o: $(SRC_DIR)/Reach/Rendering/Window.cpp 
	$(ALL_SETTINGS) -c $(SRC_DIR)/Reach/Rendering/Window.cpp -o $(OUT_DIR)/Window.o 



run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe

launch:
	make
	make run