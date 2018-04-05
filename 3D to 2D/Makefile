CC= g++
OBJECTS= final.o
LIBS= -lGL -lglut -lGLU

all: prog

prog: $(OBJECTS)
	$(CC) -o prog $(OBJECTS) $(LIBS)

final.o: final.h line3D.h final.cpp
	$(CC) -c final.cpp
