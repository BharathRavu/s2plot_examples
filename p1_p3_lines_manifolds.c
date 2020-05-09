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


void plotPnstab_new_Pts(struct Pn P, int iec, int ihc, int idc, float pn_size, float pd_size){
	int i;
        
	for( i = 0; i < P.np; i = i + 1 ){
		   if(P.sp[i]==1.0){
                    s2sci(iec);
                    s2sch(pn_size);
                    s2pt1(P.xp[i], P.yp[i], P.zp[i], 4);
	           }
		   else if(P.sp[i]==0){
               s2sci(idc);
               s2sch(pd_size);
               s2pt1(P.xp[i], P.yp[i], P.zp[i], 4);
		   }
                   else {
                   s2sci(ihc);
                   s2sch(pn_size);
                    s2pt1(P.xp[i], P.yp[i], P.zp[i], 4);

		   }
      }
}

int main(int argc, char *argv[])
{
 //  int symbol = 1;				/* Shaded sphere symbol */

	FILE *fin_p1 = fopen(argv[1], "r");
	struct Pn P1=ReadPnFile(fin_p1);
	FILE *fin_p3_1 = fopen(argv[2], "r");
	struct Pn P3_1=ReadPnFile(fin_p3_1);
	FILE *fin_p3_2 = fopen(argv[3], "r");
	struct Pn P3_2=ReadPnFile(fin_p3_2);
	FILE *fin_p3_3 = fopen(argv[4], "r");
	struct Pn P3_3=ReadPnFile(fin_p3_3);	
	FILE *fin_p2track = fopen(argv[5], "r");
	struct Pts3d Pts=ReadPts3dFile(fin_p2track);
	FILE *fin_p1re1 = fopen(argv[6], "r");
	struct Pn P1re1=ReadPnFile(fin_p1re1);
	FILE *fin_p1re1_1dmani = fopen(argv[7], "r");
	struct Pts3d mani_1d_re1=ReadPts3dFile(fin_p1re1_1dmani);

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   
//   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */

//   s2sci(7);
   s2sch(0.1);
   s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */

   pushVRMLname("P1_line_Stokes");
   plotPnstab_new_Pts(P1,18,2,3,0.1,0.2);
   pushVRMLname("P3_lines_Stokes");
   plotPnstab_new_Pts(P3_1,18,2,3,0.1,0.2);
   plotPnstab_new_Pts(P3_2,18,2,3,0.1,0.2);
   plotPnstab_new_Pts(P3_3,18,2,3,0.1,0.2);
   pushVRMLname("P3_pnt_track_Re1");
   s2sch(0.4);
   s2sci(6);
   s2pt1(Pts.xs[0], Pts.ys[0], Pts.zs[0], 4);
   s2sci(1);
   s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,1); 
   pushVRMLname("P1_pnts_Re1");
   plotPnstab_new_Pts(P1re1,18,2,3,0.4,0.4);
   pushVRMLname("1Dmanifold_Re1");
   s2sci(7);
   s2pt(mani_1d_re1.ns,mani_1d_re1.xs,mani_1d_re1.ys,mani_1d_re1.zs,1); 
   
   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
