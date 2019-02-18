CFLAGS = -g -Wall -I../../../csrc/.

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c)

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o example -lbcm2835

clean:
	-rm -f $(OBJ) example