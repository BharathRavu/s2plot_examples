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


struct Pts3d{
	float *xs;
	float *ys;
	float *zs;
    int ns;
};

struct Pts3d ReadPts3dFile(FILE *fin){
	struct Pts3d data;
	data.xs=NULL;
	data.ys=NULL;
	data.zs=NULL;
	data.ns=0;
	   float fx, fy, fz;
	   char line[256];
	   while (!feof(fin)) {
	     if (fgets(line, 255, fin)) {
	       if (sscanf(line, "%f%f%f", &fx, &fy, &fz) == 3) {
		 if (!(data.ns % STEP)) {
			 data.xs = (float *)realloc(data.xs, (data.ns+STEP) * sizeof(float));
			 data.ys = (float *)realloc(data.ys, (data.ns+STEP) * sizeof(float));
			 data.zs = (float *)realloc(data.zs, (data.ns+STEP) * sizeof(float));
		 }
		 data.xs[data.ns] = fx;
		 data.ys[data.ns] = fy;
		 data.zs[data.ns] = fz;
		 data.ns++;
	       } else {
		 fprintf(stderr, "Couldn't read 4 floats at line %d\n", data.ns);
		 exit(-1);
	       }
	     }
	   }
	   return data;
}


int main(int argc, char *argv[])
{
   int symbol = 1;				/* Shaded sphere symbol */
s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */	
	FILE *fin1 = fopen(argv[1], "r");
	struct Pts3d Stable_M=ReadPts3dFile(fin1);

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   
//   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */

//   s2sci(7);
   s2sch(0.1);	
s2pt(Stable_M.ns,Stable_M.xs,Stable_M.ys,Stable_M.zs,symbol);
s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */	
s2sci(18);
   s2sch(0.5);	
s2pt1(Stable_M.xs[0],Stable_M.ys[0],Stable_M.zs[0],4);



   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
