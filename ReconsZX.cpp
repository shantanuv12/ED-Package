#include <iostream>
#include <GL/glut.h>
#include <string>
using namespace std;

int cx=0,cz=0;
int cn,cm;
struct Line2D{
	int z1,x1,z2,x2;
	float r,g,b;
	int state;
	int total;
	string label;
};

Line2D lzx[100];
void addLine2D(){
	lzx[0].state++;
	if(lzx[0].state>2){lzx[0].state=1;}
	int st=lzx[0].state;
	if(st==1){lzx[0].total++;cn=lzx[0].total;}
	if(st==1){ lzx[cn].z1=cz;lzx[cn].x1=cx; }
	if(st==1|| st==2){ lzx[cn].z2=cz; lzx[cn].x2=cx;}
}

void drawLines(){
	for(int i=0;i<lzx[0].total+1;i++){
		glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex3f(lzx[i].x1,0,lzx[i].z1);
		glVertex3f(lzx[i].x2,0,lzx[i].z2);
		glEnd();
	}
}

void createCube(){
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(cx,0,cz);
	glutSolidCube(0.4);
	glPopMatrix();

}

void createGrid(){
	for(int i=0;i<40;i++){
		glPushMatrix();
		if(i<20){glTranslatef(i,0,0);}
		if(i>=20){glTranslatef(0,0,i-20);glRotatef(90,0,1,0);}
		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glLineWidth(1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,19);
		glEnd();
		glPopMatrix();
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-10,0,-200);
	glRotatef(-90,1,0,0);
	createGrid();
	drawLines();
	createCube();
	glutSwapBuffers();
}

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(15,1.0f,1.0f,250);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glClearColor(0.2,0.2,0.2,1);
}


void keyboard(unsigned char key,int x, int y){
        if(key=='s'){cz-=1;}
        if(key=='a'){cx-=1;}
        //if(key=='z'){cy-=1;}
        if(key=='w'){cz+=1;}
        if(key=='d'){cx+=1;}
        //if(key=='q'){cy+=1;}
        if(key=='['){addLine2D();}
        glutPostRedisplay();
}

int main(int argc, char **argv){
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE);
        glutInitWindowSize(1280,1080);
        glutCreateWindow("2D Z-X Plane");
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
		init();
        glutMainLoop();
        return 0;
}
