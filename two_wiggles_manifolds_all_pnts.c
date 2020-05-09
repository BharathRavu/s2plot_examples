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
//	for( i = 0; i < P.np; i = i + 1 ){
    for( i = 11-1; i < 15; i = i + 1 ){
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
   int symbol = 1;				/* Shaded sphere symbol */

	FILE *fin1s = fopen(argv[1], "r");
	struct Pts3d Pts1_S=ReadPts3dFile(fin1s);
	FILE *fin1u = fopen(argv[2], "r");
	struct Pts3d Pts1_U=ReadPts3dFile(fin1u);

	FILE *fin2s = fopen(argv[3], "r");
	struct Pts3d Pts2_S=ReadPts3dFile(fin2s);
	FILE *fin2u = fopen(argv[4], "r");
	struct Pts3d Pts2_U=ReadPts3dFile(fin2u);

	FILE *fin3s = fopen(argv[5], "r");
	struct Pts3d Pts3_S=ReadPts3dFile(fin3s);
	FILE *fin3u = fopen(argv[6], "r");
	struct Pts3d Pts3_U=ReadPts3dFile(fin3u);

	FILE *fin4s = fopen(argv[7], "r");
	struct Pts3d Pts4_S=ReadPts3dFile(fin4s);
	FILE *fin4u = fopen(argv[8], "r");
	struct Pts3d Pts4_U=ReadPts3dFile(fin4u);

	FILE *fin5s = fopen(argv[9], "r");
	struct Pts3d Pts5_S=ReadPts3dFile(fin5s);
	FILE *fin5u = fopen(argv[10], "r");
	struct Pts3d Pts5_U=ReadPts3dFile(fin5u);

	FILE *fin_p1 = fopen(argv[11], "r");
	struct Pn P1=ReadPnFile(fin_p1);

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   
//   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */

//   s2sci(7);
   s2sch(0.1);
   s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */

   pushVRMLname("prd_pt3_Stable");
   s2sci(1);
   s2pt(Pts1_S.ns,Pts1_S.xs,Pts1_S.ys,Pts1_S.zs,symbol);
   pushVRMLname("prd_pt3_Unstable");
   s2sci(6);
   s2pt(Pts1_U.ns,Pts1_U.xs,Pts1_U.ys,Pts1_U.zs,symbol);

   pushVRMLname("prd_pt4_Stable");
   s2sci(18);
   s2pt(Pts2_S.ns,Pts2_S.xs,Pts2_S.ys,Pts2_S.zs,symbol);
   pushVRMLname("prd_pt4_Unstable");
   s2sci(8);
   s2pt(Pts2_U.ns,Pts2_U.xs,Pts2_U.ys,Pts2_U.zs,symbol);

   pushVRMLname("prd_pt5_Stable");
   s2sci(7);
   s2pt(Pts3_S.ns,Pts3_S.xs,Pts3_S.ys,Pts3_S.zs,symbol);
   pushVRMLname("prd_pt5_Unstable");
   s2sci(6);
   s2pt(Pts3_U.ns,Pts3_U.xs,Pts3_U.ys,Pts3_U.zs,symbol);

   pushVRMLname("prd_pt6_Stable");
   s2sci(18);
   s2pt(Pts4_S.ns,Pts4_S.xs,Pts4_S.ys,Pts4_S.zs,symbol);
   pushVRMLname("prd_pt6_Unstable");
   s2sci(8);
   s2pt(Pts4_U.ns,Pts4_U.xs,Pts4_U.ys,Pts4_U.zs,symbol);

   pushVRMLname("prd_pt7_Stable");
   s2sci(1);
   s2pt(Pts5_S.ns,Pts5_S.xs,Pts5_S.ys,Pts5_S.zs,symbol);
   pushVRMLname("prd_pt7_Unstable");
   s2sci(6);
   s2pt(Pts5_U.ns,Pts5_U.xs,Pts5_U.ys,Pts5_U.zs,symbol);


   pushVRMLname("isolated_prdc_points");
s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */
plotPnstab_Pts(P1,18,2);

   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
