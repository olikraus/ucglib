CFLAGS = -g -Wall -I../../../csrc/.  -I../com/. 

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c) ../com/ucglib_com_mpsse.c

LDFLAGS += -lmpsse

OBJ = $(SRC:.c=.o)

all: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o ucglib_logo $(LDFLAGS)

clean:	
	-rm $(OBJ) ucglib_logo

