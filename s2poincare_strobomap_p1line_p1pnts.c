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
float *x = NULL;
float *y = NULL;
float *z = NULL;
float *xmf = NULL;
float *ymf = NULL;
float *zmf = NULL;
float *x2 = NULL;
float *y2 = NULL;
float *z2 = NULL;
float *x4 = NULL;
float *y4 = NULL;
float *z4 = NULL;
float *stab2 = NULL;
float *stab4 = NULL;
float *grid_iso_val = NULL;
int n = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int main(int argc, char *argv[])
{
   int symbol = 1;				/* Shaded sphere symbol */

   float fx, fy, fz, fs;
   char line[256];



   FILE *fin = fopen(argv[1], "r");
   while (!feof(fin)) {
     if (fgets(line, 255, fin)) {
       if (sscanf(line, "%f%f%f", &fx, &fy, &fz) == 3) {
	 if (!(n % STEP)) {
	   x = (float *)realloc(x, (n+STEP) * sizeof(float));
	   y = (float *)realloc(y, (n+STEP) * sizeof(float));
	   z = (float *)realloc(z, (n+STEP) * sizeof(float));
	 }
	 x[n] = fx;
	 y[n] = fy;
	 z[n] = fz;
	 n++;
       } else {
	 fprintf(stderr, "Couldn't read 3 floats at line %d\n", n);
	 exit(-1);
       }
     }
   }

   FILE *fin1 = fopen(argv[2], "r");
   while (!feof(fin1)) {
     if (fgets(line, 255, fin1)) {
       if (sscanf(line, "%f%f%f", &fx, &fy, &fz) == 3) {
	 if (!(n3 % STEP)) {
	   xmf = (float *)realloc(xmf, (n3+STEP) * sizeof(float));
	   ymf = (float *)realloc(ymf, (n3+STEP) * sizeof(float));
	   zmf = (float *)realloc(zmf, (n3+STEP) * sizeof(float));
	 }
	 xmf[n3] = fx;
	 ymf[n3] = fy;
	 zmf[n3] = fz;
	 n3++;
       } else {
	 fprintf(stderr, "Couldn't read 3 floats at line %d\n", n3);
	 exit(-1);
       }
     }
   }
   
   FILE *fin2 = fopen(argv[3], "r");
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

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   

   pushVRMLname("manifolds");
   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */
   int i;				/* Loop variables */
//   s2sci(7);
   s2pt(n,x,y,z,symbol);	/* Draw a single point */
   s2sci(6);
   s2pt(n3,xmf,ymf,zmf,symbol);	/* Draw a single point */
   pushVRMLname("LINES");
        s2slw(10);					/* Set line width */
   _s2_conelines = 1;
   float xx[2], yy[2], zz[2], stbl, xm, ym, zm, xx1[2], yy1[2], zz1[2], xx2[2], yy2[2], zz2[2];


      s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */	

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
		   s2sci(S2_PG_RED);
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

		        s2sci(S2_PG_RED);
		        s2line(2,xx2,yy2,zz2);

                        }
                    else{

                        s2sci(S2_PG_RED);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(18);
		        s2line(2,xx2,yy2,zz2);


                        }
                    s2slw(50);					/* Sets size of point */
                    s2scr(17, 0.0, 1.0, 0.0);	
		    s2sci(17);
//                    s2pt1(xm, ym, zm, 4);

	   }

   }
   s2sch(0.5);					/* Sets size of most symbols */
		    s2sci(7);
		    s2pt1(0.0, 0.258868542281411, 0.0, 4);
		    
		    for( i = 0; i < n4; i = i + 1 ){
			    if(stab4[i]==1.0){
		              		        
	                        s2sci(18);
	                        s2pt1(x4[i], y4[i], z4[i], 4);


	                        }
	                    else{

	                        s2sci(S2_PG_RED);
	                        s2pt1(x4[i], y4[i], z4[i], 4);


	                        }
		    	
		    }
		    
		    



/*   s2slw(2);			*/		/* Set line width */
/*   s2line(n2,x2,y2,z2);  */

   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
