# List of source file directories
SRC_DIRS := src src/World src/Combat src/MainMenu

# Use wildcard to find all .cpp files in the specified directories
SRCS := $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))
# SRCS := $(wildcard src/*.cpp)

#OBJS specifies which files to compile as part of the project
# OBJS = ./main.cpp ./Game.cpp ./Tile.cpp
OBJS := $(SRCS:.cpp=.o)

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

RAYLIB_PATH = C:/raylib/raylib
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -Isrc
# CFLAGS += $(RAYLIB_PATH)/src/raylib.rc.data -Wl,--subsystem,windows
LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

#LINKER_FLAGS specifies the libraries we're linking against
# LINKER_FLAGS = -lraylib -lGL -lopenal -lm -pthread -ldl -lX11 -lXrandr -l Xinerama -lXi -l Xxf86vm -lXcursor

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game.exe

#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDLIBS) -o $(OBJ_NAME)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(OBJ_NAME)

clean-object:
	rm -f $(SRCS:.cpp=.o)

