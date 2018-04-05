/*The object created by the Algorithm is displayed on the OpenGL Window using the function present in this file*/

extern "C"{
	#include "wire1.h"
}
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "screencasts.h"
#include "prototypes.h"
using namespace std;
#define PI 3.1415926535898 // Defining Pi
#define Cos(t) cos(PI/180*(t))
#define Sin(t) sin(PI/180*(t))

double dim=3.0;
int windowWidth=1280;
int windowHeight=1280;

int toggleAxes=0;
int toggleValues=1;
int toggleMode=0;
int th=0; //azimuth view angle theta
int ph=0; //elevation angle phi
int fov= 55; //field of view
int asp=1; // aspect ratio

void project(){         /*To project the content on screen*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(toggleMode){
		//Perspective
		gluPerspective(fov,asp,dim/4,4*dim);
	}
	else{
		//Orthographic
		glOrtho(-dim*asp,+dim*asp,-dim,+dim,-dim,+dim);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawAxes(){			/*Function to draw the Axes on Scree/Window*/
	if(toggleAxes){
		double len=2.0;
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINES);
		glVertex3d(0,0,0);
		glVertex3d(len,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,len,0);
		glVertex3d(0,0,0);
		glVertex3d(0,0,len);
		glEnd();
	}
}

void drawShape(){				/*Function to draw the object obtained after generating the wire frame*/
    ifstream infile("testfile.txt");
    float x1,y1,z1,x2,y2,z2;
    while(infile>>x1>>y1>>z1>>x2>>y2>>z2){
        glBegin(GL_LINES);
        glColor3f(1.0,0,0);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glEnd();
    }
}

void display(){					/*Function to display the contents on the screens*/
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

	if(toggleMode){
		double Ex=-2*dim*Sin(th)*Cos(ph);
		double Ey=+2*dim*Sin(ph);
		double Ez=+2*dim*Cos(th)*Cos(ph);

		gluLookAt(Ex,Ey,Ez,0,0,0,0,Cos(ph),0);
	}
	else{
		glRotatef(ph,1,0,0);
		glRotatef(th,0,1,0);
	}
	drawAxes();
	drawShape();

	glFlush();
	glutSwapBuffers();
}



void reshape(int width,int height){				/*Function to reshape the objects displayed on screen*/
	asp=(height>0)? (double)width/height :1;
	glViewport(0,0,width,height);
	project();
}

void windowKey(unsigned char key, int x, int y){			/*Function to which maps operations to keys input*/
	/*Keys:-
		Esc     -    Exit
		j		-	 ToggeleAxes
   		k       -    toggleValues
		l		-	 toggleMode
		u & i	-	 change field of view
		o & p	-	 change dim
		*/
	if(key==27) exit(0);
	else if(key=='j') toggleAxes=1-toggleAxes;
	else if(key=='k') toggleValues=1-toggleValues;
	else if(key=='l')toggleMode=1-toggleMode;
	else if(key=='u'&&key>1) fov-=1;
	else if(key=='i'&& key<179) fov+=1;
	else if(key=='o') dim+=0.5;
	else if(key=='p') dim-=0.5;
	project();
	glutPostRedisplay();
}

void windowSpecial(int key,int x,int y){				/*Function to map operations to Special Keys*/
	if(key==GLUT_KEY_RIGHT) th+=5;
	else if(key==GLUT_KEY_LEFT) th-=5;
	else if(key==GLUT_KEY_UP) ph+=5;
	else if(key==GLUT_KEY_DOWN) ph-=5;
	th%=360;
	ph%=360;
	project();
	glutPostRedisplay();

}


void WindowMenu(int val){				/*Function to initialise menu*/
	windowKey((unsigned char)val,0,0);
}


int main(int argc, char* argv[]){
	wire();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow(" ");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial);

	glutCreateMenu(WindowMenu);
	glutAddMenuEntry("Toggle Axes [j]",'j');
	glutAddMenuEntry("Toggle Values [k]",'k');
	glutAddMenuEntry("Toggle Mode [l]",'l');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}
