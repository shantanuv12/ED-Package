#ifndef FINAL_H
#define FINAL_H

#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include "line3D.h"
#define PI 3.1415926535898 // Defining Pi
#define Cos(t) cos(PI/180*(t))
#define Sin(t) sin(PI/180*(t))

int cx=0,cy=0,cz=0;
int cn,co;
double dim=3.0;
int windowWidth=1920;
int windowHeight=1080;

int toggleAxes=0;
int toggleValues=1;
int toggleMode=0;
int th=0; //azimuth view angle theta
int ph=0; //elevation angle phi
int fov=55; //field of view
int asp=1; // aspect ratio

void project();
void drawAxes();
void reshape();
void windowSpecial();
Line l[1000];
void addLine();
void createCube();
void createGrid();
void windowKey(unsigned char key, int x, int y);
void WindowMenu(int val);
void display();


#endif // FINAL_H
