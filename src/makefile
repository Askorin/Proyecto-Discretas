IDIR = ../inc
CC = gcc
CFLAGS = -g -Wall -Wextra -I$(IDIR)

ODIR = ./obj

_DEPS = set.h linealize.h input.h parsing.h adjacency.h path_finding.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o input.o linealize.o parsing.o set.o adjacency.o path_finding.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

main: $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~


