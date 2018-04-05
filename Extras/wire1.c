#include "wire1.h"
int eds=1;
void wire()
{
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
//printf("MAIN:\n");

printf("ENTER THE NO OF VERTICES  IN FRONT VIEW :\t");
scanf("%d",&NOVF);
printf("\n");
printf("Read The Front Vertices Set:\n");
printf("x_coordinate       z_coordinate\n");
for(i=1; i<=NOVF ; i++)
scanf("%f%f",&fv[i].x,&fv[i].z);

printf("ENTER THE NO OF VERTICES  IN TOP VIEW :\t");
scanf("%d",&NOVT);
printf("\n");
printf("Read The Top Vertices Set:\n");
printf("x_coordinate       y_coordinate\n");
for(i=1; i<=NOVT ; i++)
scanf("%f%f",&tv[i].x,&tv[i].y);

printf("ENTER THE NO OF VERTICES  IN SIDE VIEW :\t");
scanf("%d",&NOVS);
printf("\n");
printf("Read The Side Vertices Set:\n");
printf("y_coordinate       z_coordinate\n");
for(i=1; i<=NOVS ; i++)
scanf("%f%f",&sv[i].y,&sv[i].z);
/*
printf("(Front Vertices Set:)\n");
printf("x_coordinate       z_coordinate\n");
for(i=1; i<=NOVF ; i++)
printf("%f   %f\n",fv[i].x,fv[i].z);


printf("(Top Vertices Set:)\n");
printf("(x_coordinate       y_coordinate)\n");
for(i=1; i<=NOVT ; i++)
printf("%f      %f\n",tv[i].x,tv[i].y);

printf("(Side Vertices Set:)\n");
printf("y_coordinate       z_coordinate\n");
for(i=1; i<=NOVS ; i++)
printf("%f    %f\n",sv[i].y,sv[i].z);
*/
printf("EDGE INPUT:-->\n");



printf("ENTER THE NO OF EDGES IN TOP  VIEW :\t");
scanf("%d",&NOET);
printf("\n");
printf("TOP EDGE\n");
printf("start_vertex_no            finish_vertex_no\n");
for(i=1;i<=NOET;i++)
{
   scanf("%d%d",&n1,&n2);
   te[i].v_s.x = tv[n1].x;
   te[i].v_s.y = tv[n1].y;
   te[i].v_f.x = tv[n2].x;
   te[i].v_f.y = tv[n2].y;
 //  set_colour(1,0,0);
 //  line_draw(te[i].v_s.x,te[i].v_s.y,0,te[i].v_f.x,te[i].v_f.y,0);
   ydiff = tv[n1].y - tv[n2].y;
   xdiff = tv[n1].x - tv[n2].x;
   if(fabs(ydiff) < EPS)
   { te[i].ide = 1;  index = 1;}
   else   if(fabs(xdiff) < EPS)
   { te[i].ide = 5;  index = 5;}
   else
   { te[i].ide = 3;  index = 3;}
}

printf("SIDE EDGE\n");
printf("ENTER THE NO OF EDGES IN SIDE  VIEW :\t");
scanf("%d",&NOES);
printf("\n");
printf("start_vertex_no            finish_vertex_no\n");
for(i=1;i<=NOES;i++)
{
   scanf("%d%d",&n1,&n2);
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
//   set_colour(1,0,0);
//   line_draw(0,sv[n1].y,sv[n1].z,0,sv[n2].y,sv[n2].z);
}


printf("ENTER THE NO OF EDGES IN FRONT VIEW :\t");
scanf("%d",&NOEF);
printf("\n");
printf("FRONT EDGE\n");
printf("start_vertex_no            finish_vertex_no\n");
for(i=1;i<=NOEF;i++)
{
   scanf("%d%d",&n1,&n2);
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


//   printf("This edge belongs to the case  : %d \n",flag);
//   set_colour(1,0,0);
//   line_draw(fe[i].v_s.x,0,fe[i].v_s.z,fe[i].v_f.x,0,fe[i].v_f.z);
switch(flag)
{

   case 1:    	function_1(temp,sv,te,p_edge);
   		function_2(temp,se,te,p_edge);
		break;
   case 2: 	function_3(temp,tv,se,p_edge);
     		function_4(temp,te,se,p_edge);
		break;
   case 3:     	function_5(temp,te,se,p_edge);
     		function_6(temp,te,se,p_edge);
		break;

}
function_7(temp1,te,se,p_edge);

}
/*sleep(1);
clear_window();
  set_colour(1,1,0);
  line_draw(0,0,0,20,0,0);
  set_colour(1,0,0);
  line_draw(0,0,0,0,20,0);
  set_colour(0,0,1);
  line_draw(0,0,0,0,0,20);
*/
for (i=1;i<eds;i++)
{


  printf("s.no. %d  %f  %f  %f",i,p_edge[i].v_s.x,p_edge[i].v_s.y,p_edge[i].v_s.z);
  printf("\t%f  %f  %f\n",p_edge[i].v_f.x,p_edge[i].v_f.y,p_edge[i].v_f.z);
  fprintf(file, "%f %f %f",p_edge[i].v_s.x,p_edge[i].v_s.y,p_edge[i].v_s.z );
  fprintf(file, "\t%f %f %f \n",p_edge[i].v_f.x,p_edge[i].v_f.y,p_edge[i].v_f.z);

//  set_colour(0,1,0);
//  line_draw(p_edge[i].v_s.x,p_edge[i].v_s.y,p_edge[i].v_s.z, p_edge[i].v_f.x,p_edge[i].v_f.y,p_edge[i].v_f.z);

}
/*END OF THE MAIN */
fclose(file);
}

/*********************************************
 NAME : function_1()
 ROOT : Front_Edge -> Top_Edge -> Side_Vertex
 CASES DEALT:
***********************************************/

void function_1(fe,sv,te,p_edge)
edge te[],p_edge[];
edge fe;
vertex sv[];
{

  edge temp;
  int i,j;
//  printf(" I am in FUNCTION - 1:\n");
//  printf("-----------------------\n");
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
	     //printf("\t(*)\n");
	     //printf("%f %f %f\n",fe.v_s.x,sv[j].y,fe.v_s.z);
	     //printf("%f %f %f\n",fe.v_f.x,sv[j].y,fe.v_f.z);
	   }
	}
     }
    }
   }
 }


/*********************************************
 NAME : function_2()
 ROOT : Front_Edge -> Top_Edge -> Side_Edge
 CASES DEALT:
 ********************************************/
void function_2(fe,se,te,p_edge)
edge fe,se[],te[],p_edge[];
{
  int i,j;
  edge temp;
//  printf("I am in FUNCTION - 2 :\n");
//  printf("-----------------------\n");
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
	     //   printf("\t(*)\n");

		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_f.y;
		temp.v_s.y = te[i].v_s.y;
		p_edge[eds++] = temp;
	   //  printf("%f %f %f\n",fe.v_s.x,te[i].v_s.y,fe.v_s.z);
	   //  printf("%f %f %f\n",fe.v_f.x,te[i].v_f.y,fe.v_f.z);
	      }
	  	   }
	}
    }
    /*seperate and insert for reversal */
    /*................................*/

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
	     //   printf("\t(*)\n");

		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_s.y;
		temp.v_s.y = te[i].v_f.y;
		p_edge[eds++] = temp;
	   //  printf("%f %f %f\n",fe.v_s.x,se[j].v_s.y,fe.v_s.z);
	   //  printf("%f %f %f\n",fe.v_f.x,se[j].v_f.y,fe.v_f.z);
	      }
	   }
	}
    }
    /*................................*/
   }
  }
}


/************************************************
  NAME : function_3()
*************************************************/


void function_3(fe,tv,se,p_edge)
edge fe,se[],p_edge[];
vertex tv[];
{
  int i,j;
  edge temp;
//  printf(" I am in FUNCTION - 3:\n");
//  printf("-----------------------\n");
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
        //     printf("\t(*)\n");
	    // printf("%f %f %f\n",fe.v_s.x,tv[i].y,fe.v_s.z);
	    // printf("%f %f %f\n",fe.v_f.x,tv[i].y,fe.v_f.z);
	     /* CREATING A 3D POSSIBLE EDGE */
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


/*****************************/
/*  FUNCTION-4 */
/*****************************/

void function_4(fe,te,se,p_edge)
edge fe,te[],se[],p_edge[];
{
  int i,j;
  edge temp;
//  printf(" I am in FUNCTION - 4:\n");
//  printf("-----------------------\n");
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
	      //  	printf("\t(*)\n");

		        temp.v_s.x = fe.v_s.x;
		        temp.v_s.z = fe.v_s.z;
		        temp.v_s.y = se[j].v_s.y;

		        temp.v_f.x = fe.v_f.x;
			temp.v_f.z = fe.v_f.z;
			temp.v_f.y = se[j].v_f.y;
			p_edge[eds++] = temp;
	     //		printf("%f %f %f\n",fe.v_s.x,se[j].v_s.y,fe.v_s.z);
	     //		printf("%f %f %f\n",fe.v_f.x,se[j].v_f.y,fe.v_f.z);
		      }
	   }
	}
    }
    /*-----------------------*/

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
//	        	printf("\t(*)\n");

		        temp.v_s.x = fe.v_s.x;
		        temp.v_s.z = fe.v_s.z;
		        temp.v_s.y = se[j].v_f.y;

		        temp.v_f.x = fe.v_f.x;
			temp.v_f.z = fe.v_f.z;
			temp.v_f.y = se[j].v_s.y;
			p_edge[eds++] = temp;
//	     		printf("%f %f %f\n",fe.v_s.x,se[j].v_s.y,fe.v_s.z);
//	     		printf("%f %f %f\n",fe.v_f.x,se[j].v_f.y,fe.v_f.z);
		      }
	   }
	}
    }
    /*_______________________*/
   }
  }
}
/************************************************/
/*         FUNCTION--5   */

/*************************************************/

void function_5(fe,te,se,p_edge)
edge fe,te[],se[],p_edge[];
{
  int i,j;
  edge temp;
//  printf(" I am in FUNCTION - 5:\n");
//  printf("-----------------------\n");
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
	//        printf("\t(*)\n");

		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_s.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_f.y;
		p_edge[eds++] = temp;
    //            printf("%f %f %f\n",fe.v_s.x,te[i].v_s.y,fe.v_s.z);
	//        printf("%f %f %f\n",fe.v_f.x,te[i].v_f.y,fe.v_f.z);
	//	printf("%f\t",se[j].v_s.y);
	//	printf("%f\t",se[j].v_s.y);
	     }
	   }
	}
    }


/*   INSERT HERE */

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
	//        printf("\t(*)\n");

		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_f.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_s.y;
		p_edge[eds++] = temp;
    //            printf("%f %f %f\n",fe.v_s.x,te[i].v_s.y,fe.v_s.z);
	//        printf("%f %f %f\n",fe.v_f.x,te[i].v_f.y,fe.v_f.z);
	//	printf("%f\t",se[j].v_s.y);
	//	printf("%f\t",se[j].v_s.y);
	     }
	   }
	}
    }
/*..............*/

   }
  }
}
/************************************************/
/* FUNCYION - 6 */
/*************************************************/

void function_6(fe,te,se,p_edge)
edge fe,te[],se[],p_edge[];
{
  int i,j;
  edge temp;
//  printf(" I am in FUNCTION - 6:\n");
//  printf("-----------------------\n");
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
	  //      printf("\t(*)\n");

		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_s.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_f.y;
		p_edge[eds++] = temp;
    //            printf("%f %f %f\n",fe.v_s.x,te[i].v_s.y,fe.v_s.z);
	//        printf("%f %f %f\n",fe.v_f.x,te[i].v_f.y,fe.v_f.z);
	     }
	   }
	}
    }
/*   INSERT here */

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
	 //       printf("\t(*)\n");

		temp.v_s.x = fe.v_s.x;
		temp.v_s.z = fe.v_s.z;
		temp.v_s.y = te[i].v_f.y;

		temp.v_f.x = fe.v_f.x;
		temp.v_f.z = fe.v_f.z;
		temp.v_f.y = te[i].v_s.y;
		p_edge[eds++] = temp;
    //            printf("%f %f %f\n",fe.v_s.x,te[i].v_s.y,fe.v_s.z);
	//        printf("%f %f %f\n",fe.v_f.x,te[i].v_f.y,fe.v_f.z);
	     }
	   }
	}
    }
/*--------------------------*/


   }
  }
}
/************************************************/
/* FUNCTION - 7 */
/*************************************************/

void function_7(fv,te,se,p_edge)
edge te[],se[],p_edge[];
vertex fv;
{
  int i,j;
  edge temp;
//  printf(" I am in FUNCTION - 7:\n");
//  printf("-----------------------\n");
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
//	        printf("\t(*)\n");

		temp.v_s.x = fv.x;
		temp.v_s.z = fv.z;
		temp.v_s.y = te[i].v_s.y;

		temp.v_f.x = fv.x;
		temp.v_f.z = fv.z;
		temp.v_f.y = te[i].v_f.y;
		p_edge[eds++] = temp;
//                printf("%f %f %f\n",fv.x,te[i].v_s.y,fv.z);
//	        printf("%f %f %f\n",fv.x,te[i].v_f.y,fv.z);
/*		printf("%f\t",se[j].v_s.y);
		printf("%f\t",se[j].v_s.y); */
	     }
	   }
	}
    }
   }
  }
}

int main(int argc, char const *argv[]) {
	wire();
	return 0;
}
/************************************************/
