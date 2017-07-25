OBJS = source.cpp src/Shader.cpp src/GraphicsDevice.cpp src/InputHandler.cpp src/GraphicEngine.cpp src/Texture.cpp src/AudioDevice.cpp src/AudioEngine.cpp src/Hero.cpp src/Game.cpp

CC = g++

INCLUDE_PATHS = -IC:\DevLibs\SDL2-2.0.5\x86_64-w64-mingw32\include -IC:\DevLibs\SDL2-2.0.5\x86_64-w64-mingw32\include\SDL2 -IC:\DevLibs\VS\glew-2.0.0\glew-2.0.0\include -IC:\DevLibs\tinyxml -IC:\DevLibs\SDL2_image-devel-2.0.1-mingw\SDL2_image-2.0.1\x86_64-w64-mingw32\include
OPENAL_INCLUDES =  -IC:\DevLibs\SDL2_mixer-devel-2.0.1-mingw\SDL2_mixer-2.0.1\x86_64-w64-mingw32\include -IC:\DevLibs\OpenAL1.1SDK\include

LIBRARY_PATHS = -IC:\DevLibs\SDL2-2.0.5\x86_64-w64-mingw32\lib -LC:\DevLibs\glew-2.0.0\glew-2.0.0\lib -IC:\DevLibs\SDL2_image-devel-2.0.1-mingw\SDL2_image-2.0.1\x86_64-w64-mingw32\lib
OPENAL_LIBS = -LC:\DevLibs\SDL2_mixer-devel-2.0.1-mingw\SDL2_mixer-2.0.1\i686-w64-mingw32\lib -LC:\DevLibs\OpenAL1.1SDK\libs\Win32

COMPILER_FLAGS = -w -Wl, -subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lglu32 -lOpenGL32 -lglew32 -lOpenAL32

OBJ_NAME = bin/NEngine

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(OPENAL_INCLUDES) $(LIBRARY_PATHS) $(OPENAL_LIBS) $(CONPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
