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

struct Pn{
	float *xp;
	float *yp;
	float *zp;
	float *sp;
    int np;
};

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

struct Pn ReadPnFile(FILE *fin){
	struct Pn data;
	data.xp=NULL;
	data.yp=NULL;
	data.zp=NULL;
	data.sp=NULL;
	data.np=0;
	   float fx, fy, fz, fs;
	   char line[256];
	   while (!feof(fin)) {
	     if (fgets(line, 255, fin)) {
	       if (sscanf(line, "%f%f%f%f", &fx, &fy, &fz, &fs) == 4) {
		 if (!(data.np % STEP)) {
			 data.xp = (float *)realloc(data.xp, (data.np+STEP) * sizeof(float));
			 data.yp = (float *)realloc(data.yp, (data.np+STEP) * sizeof(float));
			 data.zp = (float *)realloc(data.zp, (data.np+STEP) * sizeof(float));
			 data.sp = (float *)realloc(data.sp, (data.np+STEP) * sizeof(float));
		 }
		 data.xp[data.np] = fx;
		 data.yp[data.np] = fy;
		 data.zp[data.np] = fz;
		 data.sp[data.np] = fs;
		 data.np++;
	       } else {
		 fprintf(stderr, "Couldn't read 4 floats at line %d\n", data.np);
		 exit(-1);
	       }
	     }
	   }
	   return data;
}


void plotPnstab_Pts(struct Pn P, int iec, int ihc){
	int i;
         s2sch(0.8);
	for( i = 0; i < P.np; i = i + 1 ){
 //   for( i = 1; i < 15; i = i + 1 ){
		   if(P.sp[i]==1.0){
                    s2sci(iec);
                    s2pt1(P.xp[i], P.yp[i], P.zp[i], 4);
	           }
                   else {
                   s2sci(ihc);
                    s2pt1(P.xp[i], P.yp[i], P.zp[i], 4);

		   }
      }
}

int main(int argc, char *argv[])
{
//   int symbol = 1;				/* Shaded sphere symbol */
	
   struct Pts3d Pts;
   
   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
   
    pushVRMLname("isolated_prdc_points");   
	FILE *fin_p1 = fopen(argv[1], "r");
	struct Pn P1=ReadPnFile(fin_p1);
	s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */
	plotPnstab_Pts(P1,18,2);
	
	/* Point 2 manifolds */
	
    pushVRMLname("pt2_1d_side1");  
	FILE *f1 = fopen(argv[2], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.1);
    s2sci(1);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt2_1d_side2");  
    f1 = fopen(argv[3], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.1);
    s2sci(1);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt2_2d_stable");  
    f1 = fopen(argv[4], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.3);
    s2sci(3);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,1);
	
	/* Point 3 manifolds */
	
    pushVRMLname("pt3_1d_side1");  
    f1 = fopen(argv[5], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.1);
    s2sci(1);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
	/* Point 4 manifolds */
	
    pushVRMLname("pt4_1d_side1");  
    f1 = fopen(argv[6], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.1);
    s2sci(1);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt4_1d_side2");  
    f1 = fopen(argv[7], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.1);
    s2sci(1);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
	/* Point 5 manifolds */
	
    pushVRMLname("pt5_1d_side1");  
    f1 = fopen(argv[8], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.1);
    s2sci(1);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt5_1d_side2");  
    f1 = fopen(argv[9], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.1);
    s2sci(1);
	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
	
   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
