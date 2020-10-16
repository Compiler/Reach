
CXX = g++
C++_VERSION = c++17
CXXFLAGS = -std=$(C++_VERSION) -Wall -w -g -static-libgcc -static-libstdc++

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

BOX2D_INC = outsourced/box2d/include
BOX2D_LIB = outsourced/box2d/

IMGUI_ROOT = outsourced/imgui
IMGUI_SRC = $(IMGUI_ROOT)/

INC=-I $(SRC_DIR)  -I $(GLAD_INC) -I $(GLFW_INC) -I $(GLM_ROOT) -I $(STBIMAGE_ROOT) -I $(ENTT_SRC) -I $(IMGUI_SRC) #-I $(BOX2D_INC)
LIBS = -L $(GLFW_LIB) #-L $(BOX2D_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32 #-lbox2d

OUT_DIR = bin

CALLBACK_OBJS = $(OUT_DIR)/GLFWCallbacks.o
P_CALLBACK_OBJS = 
INPUT_OBJS = $(OUT_DIR)/InputManager.o
SCENE_OBJS = $(OUT_DIR)/SceneManager.o $(OUT_DIR)/Scene.o 
LAYER_OBJS = $(OUT_DIR)/LayerManager.o $(OUT_DIR)/Layer.o

RENDERING_OBJS = $(OUT_DIR)/ParticleRenderer.o $(OUT_DIR)/BatchRenderer.o $(OUT_DIR)/ShaderProgram.o $(OUT_DIR)/TextureManager.o $(OUT_DIR)/Window.o #Box2DDebugRenderer.o
P_RENDERING_OBJS = 

FILE_OBJS = $(OUT_DIR)/FileLoaderFactory.o
P_FILE_OBJS = 

CAMERA_OBJS = $(OUT_DIR)/OrthographicCamera.o
P_CAMERA_OBJS = 

ECS_OBJS = $(OUT_DIR)/PhysicsSystem.o $(OUT_DIR)/WorldSystem.o $(OUT_DIR)/MovementSystem.o $(OUT_DIR)/ParticleSystem.o $(OUT_DIR)/Components.o $(OUT_DIR)/SystemManager.o 
P_ECS_OBJS =

ECS_COLLISION_OBJS = $(OUT_DIR)/CollisionSystem.o

UTIL_OBJS = $(OUT_DIR)/Random.o
REACH_OBJS = $(OUT_DIR)/ReachCore.o
STARTUP_OBJS = $(OUT_DIR)/StartupSystems.o
P_STARTUP_OBJS = 

#game
PLAYER_SYSTEM_OBJS = $(OUT_DIR)/InventorySystem.o
GAME_SCENES_OBJS = $(OUT_DIR)/MainMenu.o

#IMGUI
IMGUI_OBJS = imgui_impl_glfw.o imgui_impl_opengl3.o imgui.o imgui_demo.o imgui_draw.o imgui_widgets.o 
P_REACH_ENGINE_OBJS = $(P_RENDERING_OBJS) $(P_FILE_OBJS) $(P_STARTUP_OBJS) $(P_CAMERA_OBJS) $(P_CALLBACK_OBJS) $(P_ECS_OBJS)
REACH_ENGINE_OBJS = $(RENDERING_OBJS) $(REACH_OBJS) $(STARTUP_OBJS) $(FILE_OBJS) $(CALLBACK_OBJS) $(INPUT_OBJS) $(SCENE_OBJS) $(ECS_OBJS) $(UTIL_OBJS) $(LAYER_OBJS) $(CAMERA_OBJS) $(ECS_COLLISION_OBJS)
GAME_OBJS = $(PLAYER_SYSTEM_OBJS) $(GAME_SCENES_OBJS) 

LIB_OBJS = $(RENDERING_OBJS) $(STARTUP_OBJS) $(FILE_OBJS) $(CALLBACK_OBJS) $(INPUT_OBJS) $(SCENE_OBJS) $(ECS_OBJS) $(UTIL_OBJS) $(LAYER_OBJS) $(CAMERA_OBJS)
OBJS =  $(REACH_ENGINE_OBJS) $(P_OBJS)#$(GAME_OBJS) #$(IMGUI_OBJS)
P_OBJS = $(P_REACH_ENGINE_OBJS)
LIB_OUT_OBJS = $(patsubst %.o, $(OUT_DIR)/%.o, $(LIB_OBJS))
OUT_OBJECTS = $(OBJS)#$(patsubst %.o, $(OUT_DIR)/%.o, $(OBJS))
P_OUT_OBJECTS = #$(patsubst %.o, $(OUT_DIR)/%.o, $(P_OBJS))
ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) 


main: $(ENTRY_POINT) $(OBJS)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $^ $(GLAD_SRC)/glad.c $(LINKS)
	ar ru bin/libreachengine.a $(LIB_OUT_OBJS)


static_lib:
	ar ru bin/libreachengine.a $(OUT_OBJECTS)

link: $(ENTRY_POINT)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(OUT_OBJECTS) $< $(GLAD_SRC)/glad.c $(LINKS)


ds: $(LAYER_OBJS) 
	make ReachCore.o
	make link
	ar ru bin/libreachengine.a $(LIB_OUT_OBJS)
	make run

$(RENDERING_OBJS): $(OUT_DIR)/%.o: src/Reach/Rendering/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(REACH_OBJS): $(OUT_DIR)/%.o: src/Reach/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(STARTUP_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Startup/%.cpp
	$(ALL_SETTINGS) -c $< -o $@ 

$(FILE_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Files/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(CALLBACK_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Callbacks/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(INPUT_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Input/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(SCENE_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Scenes/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(ECS_OBJS): $(OUT_DIR)/%.o: src/Reach/ECS/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(UTIL_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Utils/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(LAYER_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Scenes/Layers/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(ECS_COLLISION_OBJS): $(OUT_DIR)/%.o: src/Reach/ECS/Collision/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(CAMERA_OBJS): $(OUT_DIR)/%.o: src/Reach/Tools/Cameras/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  


$(PLAYER_SYSTEM_OBJS): $(OUT_DIR)/%.o: src/Sandbox/PlayerSystems/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(GAME_SCENES_OBJS): $(OUT_DIR)/%.o: src/Sandbox/GameScenes/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  



run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe

launch:
	make
	make run