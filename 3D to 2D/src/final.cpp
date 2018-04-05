#include "final.h"
using namespace std;
void project(){                /*! Function to project the view on the screen */
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

void drawAxes(){				/*! Function to draw the 3 orthogonal Axes on the OpenGL Window */
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

void reshape(int width,int height){   /*! Function to rehape the contents of the OpenGL Window */
	asp=(height>0)? (double)width/height :1;
	glViewport(0,0,width,height);
	project();
}

void windowSpecial(int key,int x,int y){  /*! Function to assign keys to rotate the contents of the window */
	if(key==GLUT_KEY_RIGHT) th+=5;
	else if(key==GLUT_KEY_LEFT) th-=5;
	else if(key==GLUT_KEY_UP) ph+=5;
	else if(key==GLUT_KEY_DOWN) ph-=5;

	th%=360;
	ph%=360;

	project();
	glutPostRedisplay();
}

void addLine(){						/*! Function to add Lines to the Line Data Structure */
	l[0].state++;
	if(l[0].state>2){ l[0].state=1;}
	int st=l[0].state;
	if(st==1){l[0].total++; cn=l[0].total;}
	if(st==1) {l[cn].x1=cx;l[cn].y1=cy;l[cn].z1=cz;}
	if(st==1 || st==2){ l[cn].x2=cx;l[cn].y2=cy;l[cn].z2=cz; }
}

void drawLines(){					/*! Function used to dislay the lines represented by the line data structures */
	for(int i=1;i<l[0].total+1;i++){
		glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex3f(l[i].x1,l[i].y1,l[i].z1);
		glVertex3f(l[i].x2,l[i].y2,l[i].z2);
		glEnd();
	}
}

void displayFront(){					/*! Function to display Front View */
	for(int i=1;i<l[0].total+1;i++){
		glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(l[i].x1,l[i].y1,0);
		glVertex3f(l[i].x2,l[i].y2,0);
		glEnd();
	}
}

void displayTop(){					/*! Function to display Top View */
	for(int i=1;i<l[0].total+1;i++){
		glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex3f(l[i].x1,0,l[i].z1);
		glVertex3f(l[i].x2,0,l[i].z2);
		glEnd();
	}
}

void displaySide(){					/*! Function to display Side view*/
	for(int i=1;i<l[0].total+1;i++){
		glBegin(GL_LINES);
		glColor3f(1,0,1);
		glVertex3f(0,l[i].y1,l[i].z1);
		glVertex3f(0,l[i].y2,l[i].z2);
		glEnd();
	}
}

void createCube(){					/*! Function to draw the pointer/cube used to draw objects on screen*/
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(cx,cy,cz);
	glutSolidCube(0.4);
	glPopMatrix();
}

void createGrid(){					/*! Function to create 3D grid */
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
void windowKey(unsigned char key, int x, int y){    /*! Function for actions using WindowKeys */
	/*! Keys:-
		Esc     -    Exit
		j		-	 ToggeleAxes
   		k       -    toggleValues
		l		-	 toggleMode
		u & i	-	 change field of view
		o & p	-	 change dim
		w,a,z,s,d,q- change the pointer
		g		-	 viewgrid
		[		-	 create/draw Lines
		r,t,y,e -	 display f,t,s, object views resp
		]		-	 reset the pointer
		*/
	if(key==27) exit(0);
 	if(key=='j') toggleAxes=1-toggleAxes;
    if(key=='k') toggleValues=1-toggleValues;
	if(key=='l')toggleMode=1-toggleMode;
	if(key=='u'&&key>1) fov-=1;
	if(key=='i'&& key<179) fov+=1;
	if(key=='o') dim+=0.1;
	if(key=='p') dim-=0.1;
    if(key=='w'){cz+=1;}
	if(key=='a'){cx-=1;}
	if(key=='z'){cy-=1;}
	if(key=='s'){cz-=1;}
	if(key=='d'){cx+=1;}
	if(key=='q'){cy+=1;}
	if(key==']'){cx=cy=cz=0;}
	if(key=='g'){viewgrid=1-viewgrid;}
	if(key=='['){addLine();}	//1
	if(key=='r'){front=1-front;}
	if(key=='t'){top=1-top;}
	if(key=='y'){side=1-side;}
	if(key=='e'){object=1-object;}
	project();
	glutPostRedisplay();
}
void WindowMenu(int val){    /*! Function to display Menu */
	windowKey((unsigned char)val,0,0);

}

void display(){					/*! Function to display the contents of the window on screen */
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
    if(viewgrid==1){createGrid();}
	if(front==1){displayFront();}
	if(top==1){displayTop();}
	if(side==1){displaySide();}
    createCube();
	drawAxes();
	if(object==1){drawLines();}
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char* argv[]){   /*! Main function initialising the windows and performing necessary operations */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("3D Object Creator");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial);

	glutCreateMenu(WindowMenu);      /*! Created a menu which opens when we right click */
	glutAddMenuEntry("Toggle Axes [j]",'j');
	glutAddMenuEntry("Toggle Values [k]",'k');
	glutAddMenuEntry("Toggle Mode [l]",'l');
	glutAddMenuEntry("Reset Pointer [ ] ] ",']');
	glutAddMenuEntry("Display Grid [g]",'g');
	glutAddMenuEntry("Front View [r]",'r');
	glutAddMenuEntry("Top View [t]",'t');
	glutAddMenuEntry("Side View [y]",'y');
	glutAddMenuEntry("View Object [e]",'e');
	glutAddMenuEntry("Exit [Esc]",27);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
