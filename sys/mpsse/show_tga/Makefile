CFLAGS = -g -Wall -I../../../csrc/.  -I../com/. 

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c) ../com/ucglib_com_mpsse.c

LDFLAGS += -lmpsse

OBJ = $(SRC:.c=.o)

all: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o show_tga $(LDFLAGS)

clean:	
	-rm $(OBJ) show_tga

