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


void plotPnstab_Pts(struct Pn P, int iec, int ihc, float ptsize){
	int i;
         s2sch(ptsize);
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
   
	s2scr(18, 0.03137254901, 0.5725490196, 0.81568627451);  /* electric blue def */
	s2scr(21, 1-0.50196078431, 1, 1);  /* maroon */
	s2scr(22, 1-0.454901960784314,1-0.729411764705882,1-0.925490196078431);  /* saddle brown */
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

    pushVRMLname("isolated_prdc_points");   
	FILE *fin_p1 = fopen(argv[1], "r");
	struct Pn P1=ReadPnFile(fin_p1);
	plotPnstab_Pts(P1,18,2,0.8);
	
	/* Point 2 manifolds */
	
    pushVRMLname("pt7_1d_mani_stable1");  
	FILE *f1 = fopen(argv[2], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(7);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt7_1d_mani_stable2");  
    f1 = fopen(argv[3], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(7);
//    s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
    
    pushVRMLname("pt7_2d_mani_unstable");  
    f1 = fopen(argv[4], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(3);
//    s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,1);
	
    pushVRMLname("pt6_1d_mani_stable1");  
    f1 = fopen(argv[5], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(5);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt6_1d_mani_stable2");  
    f1 = fopen(argv[6], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(5);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt6_1d_mani_unstable1");  
    f1 = fopen(argv[7], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(8);
//	s2pt(3100,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt6_1d_mani_unstable2");  
    f1 = fopen(argv[8], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(8);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt5_1d_mani_stable1");  
    f1 = fopen(argv[9], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(1);
//	s2pt(1170,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt5_1d_mani_stable2");  
    f1 = fopen(argv[10], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(1);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
    
    pushVRMLname("pt5_2d_mani_unstable");  
    f1 = fopen(argv[11], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(6);
//	s2pt(20000,Pts.xs,Pts.ys,Pts.zs,1);
	
    pushVRMLname("pt4_1d_mani_stable1");  
    f1 = fopen(argv[12], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.15);
    s2sci(33);
//	s2pt(3000,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt4_1d_mani_stable2");  
    f1 = fopen(argv[13], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(33);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt4_1d_mani_unstable1");  
    f1 = fopen(argv[14], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.15);
    s2sci(32);
	s2pt(3500,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt4_1d_mani_unstable2");  
    f1 = fopen(argv[15], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.15);
    s2sci(32);
	s2pt(3500,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt3_1d_mani_stable1");  
    f1 = fopen(argv[16], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(35);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
	
    pushVRMLname("pt3to2_1d_mani");  
    f1 = fopen(argv[17], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(35);
//    s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
    
    pushVRMLname("pt3_2d_mani_unstable");  
    f1 = fopen(argv[18], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(34);
//    s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,1);
	
    pushVRMLname("pt2_1d_mani_unstable1");  
    f1 = fopen(argv[19], "r");
    Pts=ReadPts3dFile(f1);
	s2sch(0.2);
    s2sci(8);
//	s2pt(Pts.ns,Pts.xs,Pts.ys,Pts.zs,4);
//    s2line(Pts.ns,Pts.xs,Pts.ys,Pts.zs); 
	
   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
