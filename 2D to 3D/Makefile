CC=gcc
CXX=g++
OBJECTS= reconstruct.o wireframe.o
LIBS= -lGL -lglut -lGLU

all: prog

prog: $(OBJECTS)
	$(CXX) -o prog $(OBJECTS) $(LIBS)

reconstruct.o: print.h prototypes.h screencasts.h wireframe.h reconstruct.cpp
	$(CXX) -c reconstruct.cpp

wireframe.o: wireframe.h wireframe.c
	$(CC) -c wireframe.c
