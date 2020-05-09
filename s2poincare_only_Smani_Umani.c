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

   float fx, fy, fz;
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
   

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   

   pushVRMLname("manifolds");
   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */
//   int i;				/* Loop variables */
   s2sci(7);
   s2pt(n,x,y,z,symbol);	/* Draw a single point */
   s2sci(6);
   s2pt(n3,xmf,ymf,zmf,symbol);	/* Draw a single point */

		    
		  

/*   s2slw(2);			*/		/* Set line width */
/*   s2line(n2,x2,y2,z2);  */

   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
