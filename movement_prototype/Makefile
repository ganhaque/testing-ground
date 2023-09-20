.PHONY: all clean

# Define required raylib variables
PROJECT_NAME       ?= game
RAYLIB_VERSION     ?= 4.2.0
RAYLIB_PATH        ?= ..\..

# Define compiler path on Windows
COMPILER_PATH      ?= C:/raylib/w64devkit/bin

# Define default options
# One of PLATFORM_DESKTOP, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM           ?= PLATFORM_DESKTOP


# Library type used for raylib: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        ?= STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= RELEASE


# Determine PLATFORM_OS in case PLATFORM_DESKTOP selected
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    # No uname.exe on MinGW!, but OS=Windows_NT on Windows!
    # ifeq ($(UNAME),Msys) -> Windows
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS=WINDOWS
        export PATH := $(COMPILER_PATH):$(PATH)
    endif
endif

# Define raylib release directory for compiled library.
# RAYLIB_RELEASE_PATH points to provided binaries or your freshly built version
RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src


# Define default C compiler: gcc
# NOTE: define g++ compiler if using C++
CC = g++

# Define default make program: Mingw32-make
MAKE = mingw32-make

# Define compiler flags:
#  -O0                  defines optimization level (no optimization, better for debugging)
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build -> do not use in debug builds
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
# CFLAGS += -Wall -std=c99 -D_DEFAULT_SOURCE

# ifeq ($(BUILD_MODE),DEBUG)
#     CFLAGS += -g -O0
# else
#     CFLAGS += -s -O1
# endif

# Additional flags for compiler (if desired)
#CFLAGS += -Wextra -Wmissing-prototypes -Wstrict-prototypes
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        # resource file contains windows executable icon and properties
        # -Wl,--subsystem,windows hides the console window
        CFLAGS += $(RAYLIB_PATH)/src/raylib.rc.data -Wl,--subsystem,windows
    endif
endif

# Define include paths for required headers
# NOTE: Several external required libraries (stb and others)
# INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -Isrc

# Define library paths containing required libs.
LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src

# Define any libraries required on linking
# if you want to link libraries (libname.so or libname.a), use the -lname
# Libraries for Windows desktop compilation
# NOTE: WinMM library required to set high-res timer resolution
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Define a recursive wildcard function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Define all source files required
SRC_DIR = src
OBJ_DIR = obj

# Define all object files from source files
# SRC = $(call rwildcard, *.c, *.h)
SRC = $(call rwildcard, src/*.cpp, src/*.h)

#OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# OBJS ?= main.c
OBJS = $(SRC:src/%.cpp=obj/%.o)


# For Android platform we call a custom Makefile.Android
ifeq ($(PLATFORM),PLATFORM_ANDROID)
    MAKEFILE_PARAMS = -f Makefile.Android
    export PROJECT_NAME
    export SRC_DIR
else
    MAKEFILE_PARAMS = $(PROJECT_NAME)
endif

# Default target entry
# NOTE: We call this Makefile target or Makefile.Android target
all:
	$(MAKE) $(MAKEFILE_PARAMS)

# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
#%.o: %.c
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

$(OBJ_DIR)/%.o: src/%.cpp
    $(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)


# Clean everything
clean:
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        del obj\*.o $(PROJECT_NAME)$(EXT)
    endif
    ifeq ($(PLATFORM_OS),LINUX)
        find obj -type f -name '*.o' -delete
        rm -f $(PROJECT_NAME)$(EXT)
    endif
    ifeq ($(PLATFORM_OS),OSX)
        find obj -type f -name '*.o' -delete
        rm -f $(PROJECT_NAME)$(EXT)
    endif
endif
ifeq ($(PLATFORM),PLATFORM_RPI)
    find obj -type f -name '*.o' -delete
    rm -f $(PROJECT_NAME)$(EXT)
endif
ifeq ($(PLATFORM),PLATFORM_WEB)
    del obj\*.o $(PROJECT_NAME)$(EXT) $(PROJECT_NAME).html $(PROJECT_NAME).js
endif
@echo Cleaning done

