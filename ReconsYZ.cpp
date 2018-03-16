#include <iostream>
#include <GL/glut.h>
#include <string>
using namespace std;

int cz=0,cy=0;
int cn,cm;
struct Line2D{
	int z1,y1,z2,y2;
	float r,g,b;
	int state;
	int total;
	string label;
};

Line2D lyz[100];
void addLine2D(){
	lyz[0].state++;
	if(lyz[0].state>2){lyz[0].state=1;}
	int st=lyz[0].state;
	if(st==1){lyz[0].total++;cn=lyz[0].total;}
	if(st==1){ lyz[cn].z1=cz;lyz[cn].y1=cy; }
	if(st==1|| st==2){ lyz[cn].z2=cz; lyz[cn].y2=cy;}
}

void drawLines(){
	for(int i=0;i<=lyz[0].total;i++){
		glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex3f(0,lyz[i].y1,lyz[i].z1);
		glVertex3f(0,lyz[i].y2,lyz[i].z2);
		glEnd();
	}
}

void createCube(){
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(0,cy,cz);
	glutSolidCube(0.4);
	glPopMatrix();

}

void createGrid(){
	for(int i=0;i<40;i++){
		glPushMatrix();
		if(i<20){glTranslatef(0,i,0);}
		if(i>=20){glTranslatef(0,0,i-20);glRotatef(-90,1,0,0);}
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
	glRotatef(90,0,1,0);
	createGrid();
	drawLines();
	createCube();
	glutSwapBuffers();
}

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(15,1.0f,1.0f,400);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glClearColor(0.2,0.2,0.2,1);
}


void keyboard(unsigned char key,int x, int y){
        if(key=='w'){cz-=1;}
        //if(key=='a'){cx-=1;}
        if(key=='z'){cy-=1;}
        if(key=='s'){cz+=1;}
        //if(key=='d'){cx+=1;}
        if(key=='q'){cy+=1;}
        if(key=='['){addLine2D();}
        glutPostRedisplay();
}

int main(int argc, char **argv){
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE);
        glutInitWindowSize(1280,1080);
        glutCreateWindow("2D Y-Z Plane");
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
		init();
        glutMainLoop();
        return 0;
}
