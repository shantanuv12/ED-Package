#include "wireframe.h"
int eds=1;
void wire()
{                                           /*! Function that creates the wireframe of the input 2D orthographic views*/
FILE *file=fopen("testfile.txt","w");
vertex tv[100],fv[100],sv[100],p_vertex[400],temp1;
edge  te[100],fe[100], se[100],p_edge[400],temp;
int i,n1,n2,index,flag;
float xdiff,ydiff,zdiff;
void function_1();
void function_2();
void function_3();
void function_4();
void function_5();
void function_6();
void function_7();

printf("No. of vertices in Front view :\t");
scanf("%d",&NOVF);
printf("\n");
printf("Enter Front Vertices:\n");
printf("x_coordinate   z_coordinate\n");
for(i=1; i<=NOVF ; i++)
scanf("%f %f",&fv[i].x,&fv[i].z);

printf("No. of vertices in Top view :\t");
scanf("%d",&NOVT);
printf("\n");
printf("Enter Top Vertices:\n");
printf("x_coordinat   y_coordinate\n");
for(i=1; i<=NOVT ; i++)
scanf("%f %f",&tv[i].x,&tv[i].y);

printf("No. of vertices in Side View :\t");
scanf("%d",&NOVS);
printf("\n");
printf("Enter Side Vertices:\n");
printf("y_coordinate   z_coordinate\n");
for(i=1; i<=NOVS ; i++)
scanf("%f %f",&sv[i].y,&sv[i].z);

printf("Now, Input the edges:-->\n\n");

printf("No. of edges in Front View:\t");
scanf("%d",&NOET);
printf("\n");
printf("Enter Top Edges\n");
printf("Starting Vertex   Ending Vertex\n");
for(i=1;i<=NOET;i++)
{
   scanf("%d %d",&n1,&n2);
   te[i].v_s.x = tv[n1].x;
   te[i].v_s.y = tv[n1].y;
   te[i].v_f.x = tv[n2].x;
   te[i].v_f.y = tv[n2].y;
   ydiff = tv[n1].y - tv[n2].y;
   xdiff = tv[n1].x - tv[n2].x;
   if(fabs(ydiff) < EPS)
   { te[i].ide = 1;  index = 1;}
   else   if(fabs(xdiff) < EPS)
   { te[i].ide = 5;  index = 5;}
   else
   { te[i].ide = 3;  index = 3;}
}

printf("Side Edges\n");
printf("No. of edges in Side View:\t");
scanf("%d",&NOES);
printf("Enter Side Edges\n");
printf("Starting Vertex   Ending Vertex\n");
for(i=1;i<=NOES;i++)
{
   scanf("%d %d",&n1,&n2);
   se[i].v_s.y = sv[n1].y;
   se[i].v_s.z = sv[n1].z;
   se[i].v_f.y = sv[n2].y;
   se[i].v_f.z = sv[n2].z;
   ydiff = sv[n1].y - sv[n2].y;
   zdiff = sv[n1].z - sv[n2].z;
   if(fabs(ydiff) < EPS)
   { se[i].ide = 2;  index = 2;}
   else   if(fabs(zdiff) < EPS)
   { se[i].ide = 5;  index = 5;}
   else
   { se[i].ide = 3;  index = 3;}
}

printf("No. of Vertices in Front View :\t");
scanf("%d",&NOEF);
printf("Enter Front Edges\n");
printf("Starting Vertex   Ending Vertex\n");
for(i=1;i<=NOEF;i++)
{
   scanf("%d %d",&n1,&n2);
   fe[i].v_s.x = fv[n1].x;
   fe[i].v_s.z = fv[n1].z;
   fe[i].v_f.x = fv[n2].x;
   fe[i].v_f.z = fv[n2].z;
   zdiff = fv[n1].z - fv[n2].z;
   xdiff = fv[n1].x - fv[n2].x;
   if(fabs(zdiff) < EPS)
   { fe[i].ide = 1;  index = 1;}
   else if(fabs(xdiff) < EPS)
   { fe[i].ide = 2;  index = 1;}
   else
   { fe[i].ide = 3;  index = 1;}
   temp = fe[i];
   temp1 = fv[i];
   flag = temp.ide;

switch(flag)
{

   case 1:
        function_1(temp,sv,te,p_edge);
   		function_2(temp,se,te,p_edge);
		break;
   case 2:
        function_3(temp,tv,se,p_edge);
     	function_4(temp,te,se,p_edge);
		break;
   case 3:
        function_5(temp,te,se,p_edge);
     	function_6(temp,te,se,p_edge);
		break;

}
function_7(temp1,te,se,p_edge);

}
for (i=1;i<eds;i++)
{
  fprintf(file, "%f %f %f",p_edge[i].v_s.x,p_edge[i].v_s.y,p_edge[i].v_s.z );
  fprintf(file, "\t%f %f %f \n",p_edge[i].v_f.x,p_edge[i].v_f.y,p_edge[i].v_f.z);
}
fclose(file);
}

void function_1(fe,sv,te,p_edge)
edge te[],p_edge[];
edge fe;
vertex sv[];
{
/*! Function to generate possible 3D edges and vertices from FView Edges TView Edges and SView Vertices*/
  edge temp;
  int i,j;
  for(i=1;i<=NOET;i++)
  {
   if(te[i].ide==1)
   {
     if((fe.v_s.x==te[i].v_s.x AND fe.v_f.x==te[i].v_f.x) OR (fe.v_s.x==te[i].v_f.x AND
     fe.v_f.x == te[i].v_s.x))
     {
        for(j=1;j<=NOVS;j++)
        {
	   if(te[i].v_s.y==sv[j].y AND fe.v_s.z==sv[j].z)
	   {
	     temp.v_s.x = fe.v_s.x;
	     temp.v_s.z = fe.v_s.z;
	     temp.v_s.y = sv[j].y;

	     temp.v_f.x = fe.v_f.x;
	     temp.v_f.z = fe.v_f.z;
	     temp.v_f.y = sv[j].y;
	     p_edge[eds++] = temp;
	   }
	}
     }
    }
   }
 }

void function_2(fe,se,te,p_edge)
edge fe,se[],te[],p_edge[];
{
    /*! Function to generate possible 3D edges and vertices from FView Edges TView Edges and SView Edges*/
  int i,j;
  edge temp;
  for(i=1;i<=NOET;i++)
  {

   if(te[i].ide==3)
   {
     if(fe.v_s.x==te[i].v_s.x AND fe.v_f.x==te[i].v_f.x)
     {
        for(j=1;j<=NOES;j++)
        {
	   if(se[j].ide==5)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y AND fe.v_s.z==se[j].v_s.z)
		               OR
		  (te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y  AND fe.v_s.z==se[j].v_s.z))
               {
		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_f.y;
		temp.v_s.y = te[i].v_s.y;
		p_edge[eds++] = temp;
	      }
	  	   }
	}
    }
    else if(fe.v_s.x==te[i].v_f.x AND fe.v_f.x == te[i].v_s.x)
     {


        for(j=1;j<=NOES;j++)
        {
	   if(se[j].ide==5)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y AND fe.v_s.z==se[j].v_s.z)
		               OR
		  (te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y AND fe.v_s.z==se[j].v_s.z))
               {
		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_s.y;
		temp.v_s.y = te[i].v_f.y;
		p_edge[eds++] = temp;
	      }
	   }
	}
    }
   }
  }
}

void function_3(fe,tv,se,p_edge)
edge fe,se[],p_edge[];
vertex tv[];
{
    /*! Function to generate possible 3D edges and vertices from FView Edges TView Vertices and SView Edges */
  int i,j;
  edge temp;
for(j=1;j<=NOES;j++)
  {
   if(se[j].ide==2)
   {
     if((fe.v_s.z==se[j].v_s.z AND fe.v_f.z==se[j].v_f.z) OR (fe.v_s.z==se[j].v_f.z AND
     fe.v_f.z==se[j].v_s.z))
     {
        for(i=1;i<=NOET;i++)
        {
	   if(se[j].v_s.y==tv[i].y AND fe.v_s.x==tv[i].x)
	   {
         temp.v_s.x = fe.v_s.x;
	     temp.v_s.z = fe.v_s.z;
	     temp.v_s.y = tv[i].y;

	     temp.v_f.x = fe.v_f.x;
	     temp.v_f.z = fe.v_f.z;
	     temp.v_f.y = tv[i].y;
	     p_edge[eds++] = temp;
	   }
	 }
    }
   }
 }
}

void function_4(fe,te,se,p_edge)
edge fe,te[],se[],p_edge[];
{
    /*! Function to generate possible 3D edges and vertices from FView Edges TView Edges and SView Edges*/
  int i,j;
  edge temp;
  for(j=1;j<=NOES;j++)
  {
   if(se[j].ide==3)
   {
     if(fe.v_s.z==se[j].v_s.z AND fe.v_f.z==se[j].v_f.z)
     {
        for(i=1;i<=NOET;i++)
        {
	   if(te[i].ide==5)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y AND fe.v_s.x==te[i].v_s.x)
				   OR
		   (te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y AND fe.v_s.x==te[i].v_s.x))
	              {
	 	        temp.v_s.x = fe.v_s.x;
		        temp.v_s.z = fe.v_s.z;
		        temp.v_s.y = se[j].v_s.y;

		        temp.v_f.x = fe.v_f.x;
			temp.v_f.z = fe.v_f.z;
			temp.v_f.y = se[j].v_f.y;
			p_edge[eds++] = temp;
	 	      }
	   }
	}
    }
     if(fe.v_s.z==se[j].v_f.z AND fe.v_f.z == se[j].v_s.z)
     {


        for(i=1;i<=NOET;i++)
        {
	   if(te[i].ide==5)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y  AND fe.v_s.x==te[i].v_s.x)
				   OR
		   (te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y  AND fe.v_s.x==te[i].v_s.x))
	              {
		        temp.v_s.x = fe.v_s.x;
		        temp.v_s.z = fe.v_s.z;
		        temp.v_s.y = se[j].v_f.y;

		        temp.v_f.x = fe.v_f.x;
			temp.v_f.z = fe.v_f.z;
			temp.v_f.y = se[j].v_s.y;
			p_edge[eds++] = temp;
		      }
	   }
	}
    }
   }
  }
}

void function_5(fe,te,se,p_edge)
edge fe,te[],se[],p_edge[];
{
    /*! Function to generate possible 3D edges and vertices from FView Edges TView Edges and SView Edges*/
  int i,j;
  edge temp;
  for(i=1;i<=NOET;i++)
  {
   if(te[i].ide==1)
   {
     if(fe.v_s.x==te[i].v_s.x AND fe.v_f.x==te[i].v_f.x)
     {
        for(j=1;j<=NOES;j++)
        {
	   if(se[j].ide==2)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y)
		                OR
	   	(te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y))
	     {
		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_s.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_f.y;
		p_edge[eds++] = temp;
	     }
	   }
	}
    }
     if(fe.v_s.x==te[i].v_f.x AND fe.v_f.x == te[i].v_s.x)
     {
        for(j=1;j<=NOES;j++)
        {
	   if(se[j].ide==2)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y)
		                OR
	   	(te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y))
	     {
		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_f.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_s.y;
		p_edge[eds++] = temp;
	     }
	   }
	}
    }
   }
  }
}
void function_6(fe,te,se,p_edge)
edge fe,te[],se[],p_edge[];
{
    /*! Function to generate possible 3D edges and vertices from FView Edges TView Edges and SView Edges*/
  int i,j;
  edge temp;
  for(i=1;i<=NOET;i++)
  {

   if(te[i].ide==3)
   {
     if(fe.v_s.x==te[i].v_s.x AND fe.v_f.x==te[i].v_f.x)
     {
        for(j=1;j<=NOES;j++)
        {
	   if(se[j].ide==3)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y)
		                OR
	   	(te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y))
	     {
		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_s.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_f.y;
		p_edge[eds++] = temp;
	     }
	   }
	}
    }
     if(fe.v_s.x==te[i].v_f.x AND fe.v_f.x == te[i].v_s.x)
     {
        for(j=1;j<=NOES;j++)
        {
	   if(se[j].ide==3)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y)
		                OR
	   	(te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y))
	     {
		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_f.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_s.y;
		p_edge[eds++] = temp;
	     }
	   }
	}
    }
   }
  }
}
void function_7(fv,te,se,p_edge)
edge te[],se[],p_edge[];
vertex fv;
{
    /*! Function to generate possible 3D edges and vertices from FView Vertices TView Edges and SView Vertices*/
  int i,j;
  edge temp;
  for(i=1;i<=NOET;i++)
  {
   if(te[i].ide==5)
   {
     if((fv.x==te[i].v_s.x AND fv.x==te[i].v_f.x)
     			OR
	(fv.x==te[i].v_f.x AND fv.x == te[i].v_s.x))
     {
        for(j=1;j<=NOES;j++)
        {
	   if(se[j].ide==5)
	   {
	   	if((te[i].v_s.y==se[j].v_s.y AND te[i].v_f.y==se[j].v_f.y AND fv.z==se[j].v_s.z)
		                OR
	   	(te[i].v_s.y==se[j].v_f.y AND te[i].v_f.y==se[j].v_s.y AND fv.z==se[j].v_s.z))
	      {
		temp.v_s.x = fv.x;
		temp.v_s.z = fv.z;
		temp.v_s.y = te[i].v_s.y;

		temp.v_f.x = fv.x;
		temp.v_f.z = fv.z;
		temp.v_f.y = te[i].v_f.y;
		p_edge[eds++] = temp;
	     }
	   }
	}
    }
   }
  }
}
