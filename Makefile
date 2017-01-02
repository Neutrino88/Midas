SOURCE = 01_hello_SDL.c
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INC_PATHS = -Imingw_dev_lib\include\SDL2
#LIBRARY_PATHS specifies the additional library paths we'll need
LIB_PATHS = -Lmingw_dev_lib\lib
#COMPILER_FLAGS specifies the additional compilation options we're using
# -Wl,-subsystem,windows gets rid of the console window
COM_FLAGS = -Wl,-subsystem,windows -pedantic -std=c89 -Wall -Werror
#LINKER_FLAGS specifies the libraries we're linking against
LIN_FLAGS = -lmingw32 -lSDL2main -lSDL2

EXEC = program

#This is the target that compiles our executable
all : $(SOURCE)
	$(CC) $(SOURCE) $(INC_PATHS) $(LIB_PATHS) $(COM_FLAGS) $(LIN_FLAGS) -o $(EXEC)