#ifndef WIRE1_H
#define WIRE1_H
#include<stdio.h>
#include<math.h>
#define AND &&
#define OR ||
#define EPS 0.01
typedef struct{ float x,y,z;}vertex;

typedef struct{
		 vertex v_s,v_f;
		 int ide;
              }edge;
int NOVF,NOVT,NOVS,NOEF,NOET,NOES;
void wire();

#endif
