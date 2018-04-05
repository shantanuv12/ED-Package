/*! Header function defining the vertex and edge data structures*/
#ifndef WIREFRAME_H
#define WIREFRAME_H
#include<stdio.h>
#include<math.h>
#define AND &&
#define OR ||
#define EPS 0.01
typedef struct{ 
	/*! Defining the vertex data structure uses x,y,z co-ordinates as defintion */
float x,y,z;
}vertex;   

typedef struct{
/*! Defining Edges data structure which store the edge dependency between two vertices */
		 vertex v_s,v_f;
		 int ide;
              }edge;			
int NOVF,NOVT,NOVS,NOEF,NOET,NOES;	/*! Defining the variables for No. of Edges and No of vertices in Front,top and side views resp */
void wire();				/*! Defining the wire function which creates wireframe model of the orthographic projections */
#endif
