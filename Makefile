OBJS = source.cpp Shader.cpp

CC = g++

INCLUDE_PATHS = -IC:\DevLibs\SDL2-2.0.5\x86_64-w64-mingw32\include -IC:\DevLibs\VS\glew-2.0.0\glew-2.0.0\include -IC:\DevLibs\tinyxml

LIBRARY_PATHS = -IC:\DevLibs\SDL2-2.0.5\x86_64-w64-mingw32\lib -LC:\DevLibs\glew-2.0.0\glew-2.0.0\lib

COMPILER_FLAGS = -w -Wl, -subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lglu32 -lOpenGL32 -lglew32

OBJ_NAME = bin/NEngine

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CONPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
