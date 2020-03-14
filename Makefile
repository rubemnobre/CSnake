# Variables
CFLAGS  = -g
LFLAGS  = -lglut -lGL

# Main targets
snk: snk.o
		gcc -o snk snk.o $(LFLAGS)

# Source targets
snk.o: snk.c
		gcc -c snk.c $(CFLAGS)
