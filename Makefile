CC = gcc
CFLAGS =-std=c89 -Wall  -Werror -pedantic
LFLAGS =-lSDL2 -lSDL2_image

SRC_DIR = src
OBJECTS = $(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c)) 
EXECUTABLE = midas

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(SRC_DIR)/*.o $(EXECUTABLE)
