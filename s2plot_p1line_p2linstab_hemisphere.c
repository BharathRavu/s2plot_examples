/* s2poincare.c
 *
 * We would appreciate it if research outcomes using S2PLOT would
 * provide the following acknowledgement:
 *
 * "Three-dimensional visualisation was conducted with the S2PLOT
 * progamming library"
 *
 * and a reference to
 *
 * D.G.Barnes, C.J.Fluke, P.D.Bourke & O.T.Parry, 2006, Publications
 * of the Astronomical Society of Australia, 23(2), 82-93.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "s2plot.h"
extern int _s2_conelines;

#define STEP 100
float *x1 = NULL;
float *y1p = NULL;
float *z1 = NULL;
float *stab1 = NULL;

float *x2 = NULL;
float *y2 = NULL;
float *z2 = NULL;
float *stab2 = NULL;

float *x3 = NULL;
float *y3 = NULL;
float *z3 = NULL;
float *stab3 = NULL;

float *x4 = NULL;
float *y4 = NULL;
float *z4 = NULL;
float *stab4 = NULL;

float *x5 = NULL;
float *y5 = NULL;
float *z5 = NULL;
float *stab5 = NULL;

float *x6 = NULL;
float *y6 = NULL;
float *z6 = NULL;

float *x7 = NULL;
float *y7 = NULL;
float *z7 = NULL;

int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int n5 = 0;
int n6 = 0;
int n7 = 0;

int main(int argc, char *argv[])
{
//   int symbol = 1;				/* Shaded sphere symbol */

   float fx, fy, fz, fs;
   char line[256];


// reading all the P1 AND p2 POINTS WITH STABILITY
   
   FILE *fin1 = fopen(argv[1], "r");
   while (!feof(fin1)) {
     if (fgets(line, 255, fin1)) {
       if (sscanf(line, "%f%f%f%f", &fx, &fy, &fz, &fs) == 4) {
	 if (!(n1 % STEP)) {
	   x1 = (float *)realloc(x1, (n1+STEP) * sizeof(float));
	   y1p = (float *)realloc(y1p, (n1+STEP) * sizeof(float));
	   z1 = (float *)realloc(z1, (n1+STEP) * sizeof(float));
	   stab1 = (float *)realloc(stab1, (n1+STEP) * sizeof(float));
	 }
	 x1[n1] = fx;
	 y1p[n1] = fy;
	 z1[n1] = fz;
	 stab1[n1] = fs;
	 n1++;
       } else {
	 fprintf(stderr, "Couldn't read 4 floats at line %d\n", n1);
	 exit(-1);
       }
     }
   }
   
   FILE *fin2 = fopen(argv[2], "r");
   while (!feof(fin2)) {
     if (fgets(line, 255, fin2)) {
       if (sscanf(line, "%f%f%f%f", &fx, &fy, &fz, &fs) == 4) {
	 if (!(n2 % STEP)) {
	   x2 = (float *)realloc(x2, (n2+STEP) * sizeof(float));
	   y2 = (float *)realloc(y2, (n2+STEP) * sizeof(float));
	   z2 = (float *)realloc(z2, (n2+STEP) * sizeof(float));
	   stab2 = (float *)realloc(stab2, (n2+STEP) * sizeof(float));
	 }
	 x2[n2] = fx;
	 y2[n2] = fy;
	 z2[n2] = fz;
	 stab2[n2] = fs;
	 n2++;
       } else {
	 fprintf(stderr, "Couldn't read 4 floats at line %d\n", n2);
	 exit(-1);
       }
     }
   }
   
   FILE *fin3 = fopen(argv[3], "r");
   while (!feof(fin3)) {
     if (fgets(line, 255, fin3)) {
       if (sscanf(line, "%f%f%f%f", &fx, &fy, &fz, &fs) == 4) {
	 if (!(n3 % STEP)) {
	   x3 = (float *)realloc(x3, (n3+STEP) * sizeof(float));
	   y3 = (float *)realloc(y3, (n3+STEP) * sizeof(float));
	   z3 = (float *)realloc(z3, (n3+STEP) * sizeof(float));
	   stab3 = (float *)realloc(stab3, (n3+STEP) * sizeof(float));
	 }
	 x3[n3] = fx;
	 y3[n3] = fy;
	 z3[n3] = fz;
	 stab3[n3] = fs;
	 n3++;
       } else {
	 fprintf(stderr, "Couldn't read 4 floats at line %d\n", n3);
	 exit(-1);
       }
     }
   }
   
   FILE *fin4 = fopen(argv[4], "r");
   while (!feof(fin4)) {
     if (fgets(line, 255, fin4)) {
       if (sscanf(line, "%f%f%f%f", &fx, &fy, &fz, &fs) == 4) {
	 if (!(n4 % STEP)) {
	   x4 = (float *)realloc(x4, (n4+STEP) * sizeof(float));
	   y4 = (float *)realloc(y4, (n4+STEP) * sizeof(float));
	   z4 = (float *)realloc(z4, (n4+STEP) * sizeof(float));
	   stab4 = (float *)realloc(stab4, (n4+STEP) * sizeof(float));
	 }
	 x4[n4] = fx;
	 y4[n4] = fy;
	 z4[n4] = fz;
	 stab4[n4] = fs;
	 n4++;
       } else {
	 fprintf(stderr, "Couldn't read 4 floats at line %d\n", n4);
	 exit(-1);
       }
     }
   }
   
   FILE *fin5 = fopen(argv[5], "r");
   while (!feof(fin5)) {
     if (fgets(line, 255, fin5)) {
       if (sscanf(line, "%f%f%f%f", &fx, &fy, &fz, &fs) == 4) {
	 if (!(n5 % STEP)) {
	   x5 = (float *)realloc(x5, (n5+STEP) * sizeof(float));
	   y5 = (float *)realloc(y5, (n5+STEP) * sizeof(float));
	   z5 = (float *)realloc(z5, (n5+STEP) * sizeof(float));
	   stab5 = (float *)realloc(stab5, (n5+STEP) * sizeof(float));
	 }
	 x5[n5] = fx;
	 y5[n5] = fy;
	 z5[n5] = fz;
	 stab5[n5] = fs;
	 n5++;
       } else {
	 fprintf(stderr, "Couldn't read 4 floats at line %d\n", n5);
	 exit(-1);
       }
     }
   }
   

   FILE *fin6 = fopen(argv[6], "r");
   while (!feof(fin6)) {
     if (fgets(line, 255, fin6)) {
       if (sscanf(line, "%f%f%f", &fx, &fy, &fz) == 3) {
	 if (!(n6 % STEP)) {
	   x6 = (float *)realloc(x6, (n6+STEP) * sizeof(float));
	   y6 = (float *)realloc(y6, (n6+STEP) * sizeof(float));
	   z6 = (float *)realloc(z6, (n6+STEP) * sizeof(float));
	 }
	 x6[n6] = fx;
	 y6[n6] = fy;
	 z6[n6] = fz;
	 n6++;
       } else {
	 fprintf(stderr, "Couldn't read 4 floats at line %d\n", n6);
	 exit(-1);
       }
     }
   }

   FILE *fin7 = fopen(argv[7], "r");
   while (!feof(fin7)) {
     if (fgets(line, 255, fin7)) {
       if (sscanf(line, "%f%f%f", &fx, &fy, &fz) == 3) {
	 if (!(n7 % STEP)) {
	   x7 = (float *)realloc(x7, (n7+STEP) * sizeof(float));
	   y7 = (float *)realloc(y7, (n7+STEP) * sizeof(float));
	   z7 = (float *)realloc(z7, (n7+STEP) * sizeof(float));
	 }
	 x7[n7] = fx;
	 y7[n7] = fy;
	 z7[n7] = fz;
	 n7++;
       } else {
	 fprintf(stderr, "Couldn't read 4 floats at line %d\n", n7);
	 exit(-1);
       }
     }
   }
   
   // Generating figure
   
   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   

//   pushVRMLname("manifolds");
   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */
   int i;				/* Loop variables */
//   s2sci(7);
s2slw(2);					/* Set line width */
s2line(n6,x6,y6,z6);
s2line(n7,x7,y7,z7);
   
   
   float xx[2], yy[2], zz[2], stbl, xm, ym, zm, xx1[2], yy1[2], zz1[2], xx2[2], yy2[2], zz2[2];
//   _s2_conelines = 1;
   pushVRMLname("P1line");
  
   
 // P1 line with stability
   
   s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */	
   s2scr(17, 0.0, 1.0, 0.0);	

for( i = 0; i < n1-1; i = i + 1 ){

        stbl=stab1[i]+stab1[i+1];
	   if(stbl==2.0){

	   xx[0]=x1[i];
	   xx[1]=x1[i+1];
	   yy[0]=y1p[i];
	   yy[1]=y1p[i+1];
	   zz[0]=z1[i];
	   zz[1]=z1[i+1];

		   s2sci(18);
		   s2line(2,xx,yy,zz);
       }
       else if(stbl==-2.0){

	   xx[0]=x1[i];
	   xx[1]=x1[i+1];
	   yy[0]=y1p[i];
	   yy[1]=y1p[i+1];
	   zz[0]=z1[i];
	   zz[1]=z1[i+1];
		   s2sci(S2_PG_RED);
		   s2line(2,xx,yy,zz);

	   } else {

                xm=(x1[i+1]+x1[i])/2.0;
                ym=(y1p[i+1]+y1p[i])/2.0;
                zm=(z1[i+1]+z1[i])/2.0;

                    xx1[0]=x1[i];
	                xx1[1]=xm;
	                yy1[0]=y1p[i];
	                yy1[1]=ym;
	                zz1[0]=z1[i];
	                zz1[1]=zm;

	                xx2[0]=xm;
	                xx2[1]=x1[i+1];
	                yy2[0]=ym;
	                yy2[1]=y1p[i+1];
	                zz2[0]=zm;
	                zz2[1]=z1[i+1];

		    if(stab1[i]==1.0){
	              		        
                     s2sci(18);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(S2_PG_RED);
		        s2line(2,xx2,yy2,zz2);

                     }
                 else{

                     s2sci(S2_PG_RED);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(18);
		        s2line(2,xx2,yy2,zz2);


                     }

		    s2sci(17);
//                    s2pt1(xm, ym, zm, 4);

	   }

}
s2sch(0.5);					/* Sets size of most symbols */
		    s2sci(7);
		    s2pt1(0.0, 0.258868542281411, 0.0, 4);
   
   

   pushVRMLname("P2lines");

 // P2 line -1

   for( i = 0; i < n2-1; i = i + 1 ){

           stbl=stab2[i]+stab2[i+1];
	   if(stbl==2.0){

	   xx[0]=x2[i];
	   xx[1]=x2[i+1];
	   yy[0]=y2[i];
	   yy[1]=y2[i+1];
	   zz[0]=z2[i];
	   zz[1]=z2[i+1];

		   s2sci(18);
		   s2line(2,xx,yy,zz);
          }
          else if(stbl==-2.0){

	   xx[0]=x2[i];
	   xx[1]=x2[i+1];
	   yy[0]=y2[i];
	   yy[1]=y2[i+1];
	   zz[0]=z2[i];
	   zz[1]=z2[i+1];
		   s2sci(2);
		   s2line(2,xx,yy,zz);

	   } else {

                   xm=(x2[i+1]+x2[i])/2.0;
                   ym=(y2[i+1]+y2[i])/2.0;
                   zm=(z2[i+1]+z2[i])/2.0;

                        xx1[0]=x2[i];
	                xx1[1]=xm;
	                yy1[0]=y2[i];
	                yy1[1]=ym;
	                zz1[0]=z2[i];
	                zz1[1]=zm;

	                xx2[0]=xm;
	                xx2[1]=x2[i+1];
	                yy2[0]=ym;
	                yy2[1]=y2[i+1];
	                zz2[0]=zm;
	                zz2[1]=z2[i+1];

		    if(stab2[i]==1.0){
	              		        
                        s2sci(18);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(2);
		        s2line(2,xx2,yy2,zz2);

                        }
                    else{

                        s2sci(2);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(18);
		        s2line(2,xx2,yy2,zz2);


                        }
	   }
   }
   
   // P2 line -2

   for( i = 0; i < n3-1; i = i + 1 ){

           stbl=stab3[i]+stab3[i+1];
	   if(stbl==2.0){

	   xx[0]=x3[i];
	   xx[1]=x3[i+1];
	   yy[0]=y3[i];
	   yy[1]=y3[i+1];
	   zz[0]=z3[i];
	   zz[1]=z3[i+1];

		   s2sci(18);
		   s2line(2,xx,yy,zz);
          }
          else if(stbl==-2.0){

	   xx[0]=x3[i];
	   xx[1]=x3[i+1];
	   yy[0]=y3[i];
	   yy[1]=y3[i+1];
	   zz[0]=z3[i];
	   zz[1]=z3[i+1];
		   s2sci(2);
		   s2line(2,xx,yy,zz);

	   } else {

                   xm=(x3[i+1]+x3[i])/2.0;
                   ym=(y3[i+1]+y3[i])/2.0;
                   zm=(z3[i+1]+z3[i])/2.0;

                        xx1[0]=x3[i];
	                xx1[1]=xm;
	                yy1[0]=y3[i];
	                yy1[1]=ym;
	                zz1[0]=z3[i];
	                zz1[1]=zm;

	                xx2[0]=xm;
	                xx2[1]=x3[i+1];
	                yy2[0]=ym;
	                yy2[1]=y3[i+1];
	                zz2[0]=zm;
	                zz2[1]=z3[i+1];

		    if(stab3[i]==1.0){
	              		        
                        s2sci(18);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(2);
		        s2line(2,xx2,yy2,zz2);

                        }
                    else{

                        s2sci(2);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(18);
		        s2line(2,xx2,yy2,zz2);


                        }
	   }
   }
   
   // P2 line -3

      for( i = 0; i < n4-1; i = i + 1 ){

              stbl=stab4[i]+stab4[i+1];
   	   if(stbl==2.0){

   	   xx[0]=x4[i];
   	   xx[1]=x4[i+1];
   	   yy[0]=y4[i];
   	   yy[1]=y4[i+1];
   	   zz[0]=z4[i];
   	   zz[1]=z4[i+1];

   		   s2sci(18);
   		   s2line(2,xx,yy,zz);
             }
             else if(stbl==-2.0){

   	   xx[0]=x4[i];
   	   xx[1]=x4[i+1];
   	   yy[0]=y4[i];
   	   yy[1]=y4[i+1];
   	   zz[0]=z4[i];
   	   zz[1]=z4[i+1];
   		   s2sci(2);
   		   s2line(2,xx,yy,zz);

   	   } else {

                      xm=(x4[i+1]+x4[i])/2.0;
                      ym=(y4[i+1]+y4[i])/2.0;
                      zm=(z4[i+1]+z4[i])/2.0;

                           xx1[0]=x4[i];
   	                xx1[1]=xm;
   	                yy1[0]=y4[i];
   	                yy1[1]=ym;
   	                zz1[0]=z4[i];
   	                zz1[1]=zm;

   	                xx2[0]=xm;
   	                xx2[1]=x4[i+1];
   	                yy2[0]=ym;
   	                yy2[1]=y4[i+1];
   	                zz2[0]=zm;
   	                zz2[1]=z4[i+1];

   		    if(stab4[i]==1.0){
   	              		        
                           s2sci(18);
   		        s2line(2,xx1,yy1,zz1);

   		        s2sci(2);
   		        s2line(2,xx2,yy2,zz2);

                           }
                       else{

                           s2sci(2);
   		        s2line(2,xx1,yy1,zz1);

   		        s2sci(18);
   		        s2line(2,xx2,yy2,zz2);


                           }
   	   }
      }

      // P2 line -4

         for( i = 0; i < n5-1; i = i + 1 ){

                 stbl=stab5[i]+stab5[i+1];
      	   if(stbl==2.0){

      	   xx[0]=x5[i];
      	   xx[1]=x5[i+1];
      	   yy[0]=y5[i];
      	   yy[1]=y5[i+1];
      	   zz[0]=z5[i];
      	   zz[1]=z5[i+1];

      		   s2sci(18);
      		   s2line(2,xx,yy,zz);
                }
                else if(stbl==-2.0){

      	   xx[0]=x5[i];
      	   xx[1]=x5[i+1];
      	   yy[0]=y5[i];
      	   yy[1]=y5[i+1];
      	   zz[0]=z5[i];
      	   zz[1]=z5[i+1];
      		   s2sci(2);
      		   s2line(2,xx,yy,zz);

      	   } else {

                         xm=(x5[i+1]+x5[i])/2.0;
                         ym=(y5[i+1]+y5[i])/2.0;
                         zm=(z5[i+1]+z5[i])/2.0;

                              xx1[0]=x5[i];
      	                xx1[1]=xm;
      	                yy1[0]=y5[i];
      	                yy1[1]=ym;
      	                zz1[0]=z5[i];
      	                zz1[1]=zm;

      	                xx2[0]=xm;
      	                xx2[1]=x5[i+1];
      	                yy2[0]=ym;
      	                yy2[1]=y5[i+1];
      	                zz2[0]=zm;
      	                zz2[1]=z5[i+1];

      		    if(stab5[i]==1.0){
      	              		        
                              s2sci(18);
      		        s2line(2,xx1,yy1,zz1);

      		        s2sci(2);
      		        s2line(2,xx2,yy2,zz2);

                              }
                          else{

                              s2sci(2);
      		        s2line(2,xx1,yy1,zz1);

      		        s2sci(18);
      		        s2line(2,xx2,yy2,zz2);


                              }
      	   }
         }
		    
/*   s2slw(2);			*/		/* Set line width */
/*   s2line(n2,x2,y2,z2);  */

   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
