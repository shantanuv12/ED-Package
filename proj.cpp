#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
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

GLfloat vertA[3]={0.5,0.5,0.5};
GLfloat vertB[3]={-0.5,0.5,0.5};
GLfloat vertC[3]={-0.5,-0.5,0.5};
GLfloat vertD[3]={0.5,-0.5,0.5};
GLfloat vertE[3]={0.5,0.5,-0.5};
GLfloat vertF[3]={-0.5,0.5,-0.5};
GLfloat vertG[3]={-0.5,-0.5,-0.5};
GLfloat vertH[3]={0.5,-0.5,-0.5};

void project(){
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

void drawAxes(){
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

		glRasterPos3d(len,0,0);
	//	print("X");
	        glRasterPos3d(0,len,0);
	//	print("Y");
      		glRasterPos3d(0,0,len);
	//	print("Z");
	}
}

void drawValues(){
	if(toggleValues){
		glColor3f(0.8,0.8,0.8);
	//	printAt(5,5,"View Angle (th,ph)=(%d,&d)",th,ph);
	//	printAt(5,25,"Projection mode=(%s)",toggleMode?"Perspective":"Orthogonal");
		glRasterPos3fv(vertA);
	//	print("A");
		glRasterPos3fv(vertB);
	//	print("B");
		glRasterPos3fv(vertC);
	//	print("C");
		glRasterPos3fv(vertD);
	//	print("D");
		glRasterPos3fv(vertE);
	//	print("E");
		glRasterPos3fv(vertF);
	//	print("F");
		glRasterPos3fv(vertG);
	//	print("G");
		glRasterPos3fv(vertH);
	//	print("H");
	}
}



void drawShape(){
	glBegin(GL_QUADS);
	glColor3f(1.0,1.0,1.0);
	glVertex3fv(vertA);
	glVertex3fv(vertB);
	glVertex3fv(vertC);
	glVertex3fv(vertD);
	glColor3f(1.0,0.0,0.0);
	glVertex3fv(vertE);
	glVertex3fv(vertF);
	glVertex3fv(vertH);
	glVertex3fv(vertG);
	glColor3f(0.0,1.0,0.0);
	glVertex3fv(vertA);
	glVertex3fv(vertF);
	glVertex3fv(vertB);
	glVertex3fv(vertE);
	glColor3f(0.0,0.0,0.1);
	glVertex3fv(vertA);
	glVertex3fv(vertF);
	glVertex3fv(vertD);
	glVertex3fv(vertG);
	glColor3f(1.0,1.0,0.0);
	glVertex3fv(vertB);
	glVertex3fv(vertE);
	glVertex3fv(vertC);
	glVertex3fv(vertH);
	glColor3f(0.0,1.0,1.0);
	glVertex3fv(vertD);
	glVertex3fv(vertG);
	glVertex3fv(vertH);
	glVertex3fv(vertC);
	glEnd();
}

void display(){
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
	drawValues();
	drawShape();

	glFlush();
	glutSwapBuffers();
}



void reshape(int width,int height){
	asp=(height>0)? (double)width/height :1;
	glViewport(0,0,width,height);
	project();
}

void windowKey(unsigned char key, int x, int y){
	if(key==27) exit(0);
	else if(key=='j') toggleAxes=1-toggleAxes;
	else if(key=='k') toggleValues=1-toggleValues;
	else if(key=='l')toggleMode=1-toggleMode;
	else if(key=='u'&&key>1) fov-=1;
	else if(key=='i'&& key<179) fov+=1;
	else if(key=='o') dim+=0.1;
	else if(key=='p') dim-=0.1;
	project();
	glutPostRedisplay();
}

void windowSpecial(int key,int x,int y){
	if(key==GLUT_KEY_RIGHT) th+=5;
	else if(key==GLUT_KEY_LEFT) th-=5;
	else if(key==GLUT_KEY_UP) ph+=5;
	else if(key==GLUT_KEY_DOWN) ph-=5;

	th%=360;
	ph%=360;

	project();
	glutPostRedisplay();

}


void WindowMenu(int val){
	windowKey((unsigned char)val,0,0);
}


int main(int argc, char* argv[]){
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
