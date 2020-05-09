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
		 if (!(data.ns % STEP)) {
			 data.xs = (float *)realloc(data.xs, (data.ns+STEP) * sizeof(float));
			 data.ys = (float *)realloc(data.ys, (data.ns+STEP) * sizeof(float));
			 data.zs = (float *)realloc(data.zs, (data.ns+STEP) * sizeof(float));
		 }
		select.xs[select.ns] = ptstot.xs[i];
		select.ys[select.ns] = ptstot.ys[i];
		select.zs[select.ns] = ptstot.zs[i];
		select.ns++;
	}
	return select;

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
/* ./p1_p2_lines_cuboid p1_pnts_beta_2.0.dat p2line.dat p2pnt_track.dat p1_pnts_re1_beta_2.0.dat beta_2_strobo_sec_maniflds_all_forw.dat beta_2_strobo_sec_maniflds_all_forw_part2.dat beta_2_pt15_maniflds_backw_part1.dat beta_2_pt15_maniflds_forw_part1.dat beta_2_pt15_maniflds_backw_part2.dat beta_2_pt15_maniflds_backw_part2.dat beta_2_pt15_maniflds_forw_part2.dat sphere_initial.dat 
 *  */
	FILE *fin_p1 = fopen(argv[1], "r");
	struct Pn P1=ReadPnFile(fin_p1);
	FILE *fin_p2 = fopen(argv[2], "r");
	struct Pn P2=ReadPnFile(fin_p2);
	FILE *fin_p1re1 = fopen(argv[3], "r");
	struct Pn P1re1=ReadPnFile(fin_p1re1);

	
	FILE *pnts1 = fopen(argv[4], "r");
	struct Pts3d ptsprtf0=ReadPts3dFile(pnts1);
	
	FILE *pnts2 = fopen(argv[5], "r");
	struct Pts3d ptsprtf5=ReadPts3dFile(pnts2);
	
	FILE *pnts3 = fopen(argv[6], "r");
	struct Pts3d ptsprtf10=ReadPts3dFile(pnts3);
	
	FILE *pnts4 = fopen(argv[7], "r");
	struct Pts3d ptsprtf15=ReadPts3dFile(pnts4);
	
	FILE *pnts5 = fopen(argv[8], "r");
	struct Pts3d ptsprtf20=ReadPts3dFile(pnts5);
	
	
	
	FILE *pnts6 = fopen(argv[9], "r");
	struct Pts3d ptsprtb5=ReadPts3dFile(pnts6);
	
	FILE *pnts7 = fopen(argv[10], "r");
	struct Pts3d ptsprtb10=ReadPts3dFile(pnts7);
	
	FILE *pnts8 = fopen(argv[11], "r");
	struct Pts3d ptsprtb15=ReadPts3dFile(pnts8);
	
	FILE *pnts9 = fopen(argv[12], "r");
	struct Pts3d ptsprtb20=ReadPts3dFile(pnts9);
	
/*	FILE *spr5_b = fopen(argv[12], "r");
	struct Pts3d spr5b=ReadPts3dFile(spr5_b);
	FILE *spr0_i = fopen(argv[13], "r");
	struct Pts3d spr0=ReadPts3dFile(spr0_i); */
	
	
   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   
//   s2sch(0.8);					/* Sets size of most symbols */

 /*  s2sci(S2_PG_BLACK); */

//   s2sci(7);
   s2sch(0.1);
   s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */
  	s2scr(21, 0.50196078431, 1, 1);  /* maroon */
  	s2scr(22, 0.454901960784314,0.729411764705882,0.925490196078431);  /* saddle brown */
  	s2scr(23, 1-0,1-0.921568627450980,1-0.423529411764706);  /* deep pink */
  	s2scr(24, 1-0.498039215686275,1-1,1-0.498039215686275);  /* purple */
  	s2scr(26, 1-0.419607843137255,1-1,1-0.172549019607843);  /* dark violet */
  	s2scr(27, 1-0.705882352941176,1-1,1-0.490196078431373);  /* indigo */
  	s2scr(29, 1-1,1-1,1-0.498039215686275);  /*navy */
  	s2scr(30, 0.901960784313726,0.901960784313726,0.980392156862745);  /*lavender */
  	s2scr(31, 0.960784313725490,0.870588235294118,0.701960784313725);  /*wheat */
  	s2scr(32, 0.980392156862745,0.501960784313726,0.447058823529412);  /*salmon */
  	s2scr(33, 0.529411764705882,0.807843137254902,0.921568627450980);  /*sky blue */	
  	s2scr(34, 0.823529411764706,0.411764705882353,0.117647058823529);  /*chocolate*/
  	s2scr(35, 0.678431372549020,1,0.184313725490196);  /*green yellow*/
  	
   pushVRMLname("P1_line_Stokes");
   plotPnstab_new_Pts(P1,18,2,3,0.1,0.2);
   pushVRMLname("P2_line_Stokes");
   plotPnstab_new_Pts(P2,18,2,3,0.1,0.2); 
   pushVRMLname("P1_pnts_Re1");
   plotPnstab_new_Pts(P1re1,18,2,3,0.4,0.4);
   
//   s2sci(6);
//   s2pt(ptscuboid_for.ns,ptscuboid_for.xs,ptscuboid_for.ys,ptscuboid_for.zs,1);
   
//   double nms=4752.0;   
   pushVRMLname("cuboid_initial");
 //  struct Pts3d ptsprtf0=ReadSelectedPts3d(ptscuboid_for, 0, 4752);
   s2sci(7);
   s2pt(ptsprtf0.ns,ptsprtf0.xs,ptsprtf0.ys,ptsprtf0.zs,1);
   
   s2sci(1);
   pushVRMLname("cuboid_forw_5prds");
//   struct Pts3d ptsprtf5=ReadSelectedPts3d(ptscuboid_for, 5*4752, 6*4752);
   s2pt(ptsprtf5.ns,ptsprtf5.xs,ptsprtf5.ys,ptsprtf5.zs,1);
   
   pushVRMLname("cuboid_forw_10prds");
//   struct Pts3d ptsprtf10=ReadSelectedPts3d(ptscuboid_for, 10*nms, 11*nms);
   s2pt(ptsprtf10.ns,ptsprtf10.xs,ptsprtf10.ys,ptsprtf10.zs,1);
   
   pushVRMLname("cuboid_forw_15prds");
//   struct Pts3d ptsprtf15=ReadSelectedPts3d(ptscuboid_for, 15*nms, 16*nms);
   s2pt(ptsprtf15.ns,ptsprtf15.xs,ptsprtf15.ys,ptsprtf15.zs,1);
   
   pushVRMLname("cuboid_forw_20prds");
//   struct Pts3d ptsprtf20=ReadSelectedPts3d(ptscuboid_for, 20*nms, 21*nms);
   s2pt(ptsprtf20.ns,ptsprtf20.xs,ptsprtf20.ys,ptsprtf20.zs,1);
   
   s2sci(6);
   pushVRMLname("cuboid_back_5prds");
//   struct Pts3d ptsprtb5=ReadSelectedPts3d(ptscuboid_back, 5*nms, 6*nms);
   s2pt(ptsprtb5.ns,ptsprtb5.xs,ptsprtb5.ys,ptsprtb5.zs,1);
   
   pushVRMLname("cuboid_back_10prds");
//   struct Pts3d ptsprtb10=ReadSelectedPts3d(ptscuboid_back, 10*nms, 11*nms);
   s2pt(ptsprtb10.ns,ptsprtb10.xs,ptsprtb10.ys,ptsprtb10.zs,1);
   
   pushVRMLname("cuboid_back_15prds");
 //  struct Pts3d ptsprtb15=ReadSelectedPts3d(ptscuboid_back, 15*nms, 16*nms);
   s2pt(ptsprtb15.ns,ptsprtb15.xs,ptsprtb15.ys,ptsprtb15.zs,1);
   
   pushVRMLname("cuboid_back_20prds");
//   struct Pts3d ptsprtb20=ReadSelectedPts3d(ptscuboid_back, 20*nms, 21*nms);
   s2pt(ptsprtb20.ns,ptsprtb20.xs,ptsprtb20.ys,ptsprtb20.zs,1);
   
   
   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
