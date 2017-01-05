CC = gcc
CFLAGS =-std=c89 -Wall  -Werror -pedantic
LFLAGS =-lSDL2 -lSDL2_image

SRC_DIR = src
OBJECTS = $(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c)) 
BIN_DIR = bin
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@ $(LFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(SRC_DIR)/*.o $(BIN_DIR)/$(EXECUTABLE)
