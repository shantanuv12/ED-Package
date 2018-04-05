CC=gcc
CXX=g++
ODIR=/obj
IDIR=/include
SDIR=/src
OBJECTS= $(ODIR)/reconstruct.o $(ODIR)/wireframe.o
LIBS= -lGL -lglut -lGLU

all: prog

prog: $(OBJECTS)
	$(CXX) -o prog $(OBJECTS) $(LIBS)

$(ODIR)/reconstruct.o: $(IDIR)/print.h $(IDIR)/prototypes.h $(IDIR)/screencasts.h $(IDIR)/wireframe.h $(SDIR)/reconstruct.cpp
	$(CXX) -c $(SDIR)/reconstruct.cpp

$(ODIR/)wireframe.o: $(IDIR)/wireframe.h $(SDIR)/wireframe.c
	$(CC) -c wireframe.c

.PHONY: clean
	rm -f $(ODIR)/*.o prog

