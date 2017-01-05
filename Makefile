CC = gcc
CFLAGS =-std=c89 -Wall  -Werror -pedantic
LFLAGS =-lSDL2 -lSDL2_image
EXE = bin/game
SRC = src
OFILES = $(patsubst %.c,%.o,$(wildcard $(SRC)/*.c)) 

all: $(EXE)

$(EXE): $(OFILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $^  -o $@

clean:
	rm $(SRC)/*.o && rm $(EXE)
