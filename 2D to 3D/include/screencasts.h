/*! Header File for including all the required libraries for Writing on screen */

#ifndef SCREENCASTS
#define SCREENCASTS

#include <iostream>
#include <math.h>
#include <string.h>
#include <time.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLTEXT_PROTOTYPES
#ifdef __LINUX__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "prototypes.h"
#endif
