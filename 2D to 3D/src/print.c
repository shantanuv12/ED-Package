/*! Header file containing all the print functions to display items on OpenGL Window*/

#include "screencasts.h"

#define LEN 8192	/*! Maximum length of the characters which we can print */
void printv(va_list args, const char* format)
{
	/*! Function to give the value which we have to print on screen */
	  char buf[LEN];
	    char* ch=buf;
	      vsnprintf(buf,LEN,format,args);
	        while (*ch)
			    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void print(const char* format, ...)
{
	/*! Function to print the character at screen*/
	  va_list args;
	    va_start(args,format);
	      printv(args,format);
	        va_end(args);
}

void printAt(int x, int y, const char* format, ...)
{
	/*!  Function to point at position at which we are displaying the character*/
	  va_list args;
	    glWindowPos2i(x,y);
	      va_start(args,format);
	        printv(args,format);
		  va_end(args);
}

void errCheck(char* where)
{
	/*!
	   Convenience method to print out OpenGL errors to stderr
	    */
	   int err = glGetError();
	      if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
