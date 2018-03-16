#include <iostream>
#include <GL/glut.h>
#include <string>
using namespace std;

int cx=0,cy=0;
int cn,cm;
struct Line2D{
	int x1,y1,x2,y2;
	float r,g,b;
	int state;
	int total;
	string label;
};

Line2D lxy[100];
void addLine2D(){
	l[0].state++;
	if(l[0].state>2){l[0].state=1;}
	int st=l[0].state;
	if(st==1){l[0].total++;cn=l[0].total;}
	if(st==1){ l[cn].x1=cx;l[cn].y1=cy; }
	if(st==1|| st==2){ l[cn].x2=cx; l[cn].y2=cy;}
}

void drawLines(){
	for(int i=0;i<=l[0].total;i++){
		glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex2f(l[i].x1,l[i].y1);
		glVertex2f(l[i].x2,l[i].y2);
		glEnd();
	}
}

void createCube(){
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(cx,cy,0);
	glutSolidCube(0.4);
	glPopMatrix();

}

void createGrid(){
	for(int i=0;i<40;i++){
		glPushMatrix();
		if(i<20){glTranslatef(i,0,0);}
		if(i>=20){glTranslatef(0,i-20,0);glRotatef(-90,0,0,1);}
		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glLineWidth(1);
		glVertex2f(0,0);
		glVertex2f(0,19);
		glEnd();
		glPopMatrix();
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-10,0,-75);
	glRotatef(0,0,0,0);
	createGrid();
	drawLines();
	createCube();
	glutSwapBuffers();
}

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35,1.0f,1.0f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glClearColor(0.2,0.2,0.2,1);
}


void keyboard(unsigned char key,int x, int y){
       // if(key=='w'){cz-=1;}
        if(key=='a'){cx-=1;}
        if(key=='z'){cy-=1;}
       // if(key=='s'){cz+=1;}
        if(key=='d'){cx+=1;}
        if(key=='q'){cy+=1;}
        if(key=='['){addLine2D();}
        glutPostRedisplay();
}

int main(int argc, char **argv){
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE);
        glutInitWindowSize(1280,1080);
        glutCreateWindow("2D X-Y Plane");
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
		init();
        glutMainLoop();
        return 0;
}
