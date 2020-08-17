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
ENTT_ROOT = outsourced/entt
ENTT_SRC = $(ENTT_ROOT)
INC=-I $(SRC_DIR)  -I $(GLAD_INC) -I $(GLFW_INC) -I $(GLM_ROOT) -I $(STBIMAGE_ROOT) -I $(ENTT_SRC)
LIBS = -L $(GLFW_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32

OUT_DIR = bin
CALLBACK_OBJS = GLFWCallbacks.o
INPUT_OBJS = InputManager.o
SCENE_OBJS = SceneManager.o Scene.o 
RENDERING_OBJS = Window.o BatchRenderer.o ShaderProgram.o
FILE_OBJS = FileLoaderFactory.o
REACH_OBJS = ReachCore.o
STARTUP_OBJS = StartupSystems.o
OBJS = $(RENDERING_OBJS) $(REACH_OBJS) $(STARTUP_OBJS) $(FILE_OBJS) $(CALLBACK_OBJS) $(INPUT_OBJS) $(SCENE_OBJS)

OUT_OBJECTS = $(patsubst %.o, $(OUT_DIR)/%.o, $(OBJS))
ALL_SETTINGS = $(CXX) $(CXXFLAGS) -pthread $(LIBS) $(INC) 

all: main


main: $(ENTRY_POINT) $(OBJS)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(OUT_OBJECTS) $< $(GLAD_SRC)/glad.c $(LINKS)

$(RENDERING_OBJS): %.o: src/Reach/Rendering/%.cpp
	$(ALL_SETTINGS) -c $< -o $(OUT_DIR)/$@  

$(REACH_OBJS): %.o: src/Reach/%.cpp
	$(ALL_SETTINGS) -c $< -o $(OUT_DIR)/$@  

$(STARTUP_OBJS): %.o: src/Reach/Tools/Startup/%.cpp
	$(ALL_SETTINGS) -c $< -o $(OUT_DIR)/$@ 

$(FILE_OBJS): %.o: src/Reach/Tools/Files/%.cpp
	$(ALL_SETTINGS) -c $< -o $(OUT_DIR)/$@  

$(CALLBACK_OBJS): %.o: src/Reach/Tools/Callbacks/%.cpp
	$(ALL_SETTINGS) -c $< -o $(OUT_DIR)/$@  

$(INPUT_OBJS): %.o: src/Reach/Tools/Input/%.cpp
	$(ALL_SETTINGS) -c $< -o $(OUT_DIR)/$@  

$(SCENE_OBJS): %.o: src/Reach/Tools/Scenes/%.cpp
	$(ALL_SETTINGS) -c $< -o $(OUT_DIR)/$@  


run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe

launch:
	make
	make run