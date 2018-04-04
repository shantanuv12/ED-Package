#include <iostream>
#include <GL/glut.h>
#include "line3D.h"
using namespace std;

int cx=0,cy=0,cz=0;
int cn,co;
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
/*
void createGridV(){
    int i;
    for(i=0;i<40;i++){
          glPushMatrix();
          if(i<20){
               glTranslatef(0,i,0);
          }
          if(i>=20){
               glTranslatef(i-20,0,0);
               glRotatef(-90,1,0,0);
          }
          glBegin(GL_LINES);
          glColor3f(1,1,1);
          glLineWidth(1);
          glVertex3f(0,-0.1,0);
          glVertex3f(19,-0.1,0);
          glEnd();
          glPopMatrix();
       }
}
*/
void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-13,0,-45);
	glRotatef(40,1,1,0);
	createGrid();
//	createGridV();
	drawLines();
	drawQuads();
	createCube();
	glutSwapBuffers();
}
void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35,1.0f,1.0f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2,0.2,0.2,1);

}

void keyboard(unsigned char key,int x, int y){
	if(key=='w'){cz-=1;}
	if(key=='a'){cx-=1;}
	if(key=='z'){cy-=1;}
	if(key=='s'){cz+=1;}
	if(key=='d'){cx+=1;}
	if(key=='q'){cy+=1;}

	if(key=='['){addLine();}	//1
	if(key==']'){addQuad();} //2

	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1280,1080);
	glutCreateWindow("3D Object Creator");
//	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
