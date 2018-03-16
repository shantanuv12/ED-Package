#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
using namespace std;
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
int fov= 55; //field of view
int asp=1; // aspect ratio


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

void reshape(int width,int height){
	asp=(height>0)? (double)width/height :1;
	glViewport(0,0,width,height);
	project();
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
struct Line{
	int x1,y1,z1,x2,y2,z2;
	float r,g,b;
	int state;
	int total;

};
Line l[1000];
void addLine(){
	l[0].state++;
	if(l[0].state>2){ l[0].state=1;}
	int st=l[0].state;
	if(st==1){l[0].total++; cn=l[0].total;}
	if(st==1) {l[cn].x1=cx;l[cn].y1=cy;l[cn].z1=cz;}
	if(st==1 || st==2){ l[cn].x2=cx;l[cn].y2=cy;l[cn].z2=cz; }
}

void drawLines(){
	for(int i=1;i<l[0].total+1;i++){
		glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex3f(l[i].x1,l[i].y1,l[i].z1);
		glVertex3f(l[i].x2,l[i].y2,l[i].z2);
		glEnd();
	}
}

struct Quads{
	int x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4;
	float r,g,b;
	int state;
	int total;

};
Quads q[1000];
void addQuad(){
	q[0].state++;
	if(q[0].state>4){ q[0].state=1;}
        int st=q[0].state;
        if(st==1){q[0].total++; co=q[0].total;}
        if(st==1) {q[co].x1=cx;q[co].y1=cy;q[co].z1=cz;}
        if(st==1 || st==2){ q[co].x2=cx;q[co].y2=cy;q[co].z2=cz; }
	    if(st==1 || st==2 || st==3){ q[co].x3=cx;q[co].y3=cy;q[co].z3=cz; }
	    if(st==1 || st==2 || st==3 || st==4){ q[co].x4=cx;q[co].y4=cy;q[co].z4=cz;}
}

void drawQuads(){
	for(int i=0;i<q[0].total;i++){
		glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex3f(q[i].x1,q[i].y1,q[i].z1);
		glVertex3f(q[i].x2,q[i].y2,q[i].z2);
		glVertex3f(q[i].x3,q[i].y3,q[i].z3);
		glVertex3f(q[i].x4,q[i].y4,q[i].z4);
		glEnd();
	}
}

void createCube(){
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(cx,cy,cz);
	glutSolidCube(0.4);
	glPopMatrix();
}

void createGrid(){
	int i,j,k;
        for(i=0;i<40;i++){
                glPushMatrix();
		if(i<20){glTranslatef(0,0,i);}
		if(i>=20){glTranslatef(i-20,0,0);glRotatef(-90,0,1,0);}
                glBegin(GL_LINES);
                glColor3f(1,1,1);
		glLineWidth(1);
                glVertex3f(0,0,0);
                glVertex3f(19,0,0);
                glEnd();
                glPopMatrix();
	}
	for(j=0;j<40;j++){
		glPushMatrix();
		if(j<20){glTranslatef(0,j,0);}
		if(j>=20){glTranslatef(0,0,j-20);glRotatef(-90,1,0,0);}
		glBegin(GL_LINES);
		glColor3f(10,10,10);
		glLineWidth(1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,19);
		glEnd();
		glPopMatrix();
	}

	for(k=0;k<40;k++){
		glPushMatrix();
		if(k<20){glTranslatef(k,0,0);}
		if(k>=20){glTranslatef(0,k-20,0);glRotatef(-90,0,0,1);}
		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glLineWidth(1);
		glVertex3f(0,0,0);
		glVertex3f(0,19,0);
		glEnd();
		glPopMatrix();
	}

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
    else if(key=='w'){cz-=1;}
	else if(key=='a'){cx-=1;}
	else if(key=='z'){cy-=1;}
	else if(key=='s'){cz+=1;}
	else if(key=='d'){cx+=1;}
	else if(key=='q'){cy+=1;}

	else if(key=='['){addLine();}	//1
	else if(key==']'){addQuad();}
	project();
	glutPostRedisplay();
}

void WindowMenu(int val){
	windowKey((unsigned char)val,0,0);

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
    createGrid();
    createCube();
	drawAxes();
	drawLines();
	drawQuads();
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("3D Object Creator");

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
