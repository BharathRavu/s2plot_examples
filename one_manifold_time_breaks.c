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

struct Pts3d ReadSelectedPts3d(struct Pts3d ptstot, int i1, int i2){
	int i;
	struct Pts3d select;
	select.xs=NULL;
	select.ys=NULL;
	select.zs=NULL;
	select.ns=0;
	for(i=i1;i<i2;i=i+1){
		select.xs[select.ns] = ptstot.xs[i];
		select.ys[select.ns] = ptstot.ys[i];
		select.zs[select.ns] = ptstot.zs[i];
		select.ns++;
	}
	return select;

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
	struct Pts3d Pts1=ReadPts3dFile(fin1s);

   double nms=floor(Pts1.ns/6.0);
   struct Pts3d ptsprt1=ReadSelectedPts3d(Pts1, 0, nms);
   struct Pts3d ptsprt2=ReadSelectedPts3d(Pts1, nms, 2*nms);
   struct Pts3d ptsprt3=ReadSelectedPts3d(Pts1, 2*nms, 3*nms);
   struct Pts3d ptsprt4=ReadSelectedPts3d(Pts1, 3*nms, 4*nms);
   struct Pts3d ptsprt5=ReadSelectedPts3d(Pts1, 4*nms, 5*nms);
   struct Pts3d ptsprt6=ReadSelectedPts3d(Pts1, 5*nms, 6*nms);


	FILE *fin_p1 = fopen(argv[2], "r");
	struct Pn P1=ReadPnFile(fin_p1);

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   
//   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */

//   s2sci(7);
   s2sch(0.7);
   s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */

   pushVRMLname("segment1");
   s2sci(1);
   s2pt(Pts1.ns,Pts1.xs,Pts1.ys,Pts1.zs,symbol);

   pushVRMLname("segment2");
   s2sci(18);
   s2pt(ptsprt2.ns,ptsprt2.xs,ptsprt2.ys,ptsprt2.zs,symbol);

   pushVRMLname("segment3");
   s2sci(6);
   s2pt(ptsprt3.ns,ptsprt3.xs,ptsprt3.ys,ptsprt3.zs,symbol);

   pushVRMLname("segment4");
   s2sci(7);
   s2pt(ptsprt4.ns,ptsprt4.xs,ptsprt4.ys,ptsprt4.zs,symbol);

   pushVRMLname("segment5");
   s2sci(8);
   s2pt(ptsprt5.ns,ptsprt5.xs,ptsprt5.ys,ptsprt5.zs,symbol);

   pushVRMLname("segment6");
   s2sci(2);
   s2pt(ptsprt6.ns,ptsprt6.xs,ptsprt6.ys,ptsprt6.zs,symbol);



   pushVRMLname("isolated_prdc_points");
s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */
plotPnstab_Pts(P1,18,2);

   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
