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
//   int symbol = 1;				/* Shaded sphere symbol */
	FILE *fin1 = fopen(argv[1], "r");
	struct Pts3d Pts1=ReadPts3dFile(fin1);
	FILE *fin2 = fopen(argv[2], "r");
	struct Pts3d Pts2=ReadPts3dFile(fin2);
	FILE *fin3 = fopen(argv[3], "r");
	struct Pts3d Pts3=ReadPts3dFile(fin3);
	FILE *fin4 = fopen(argv[4], "r");
	struct Pts3d Pts4=ReadPts3dFile(fin4);
	FILE *fin5 = fopen(argv[5], "r");
	struct Pts3d Pts5=ReadPts3dFile(fin5);
	FILE *fin6 = fopen(argv[6], "r");
	struct Pts3d Pts6=ReadPts3dFile(fin6);
	FILE *fin7 = fopen(argv[7], "r");
	struct Pts3d Pts7=ReadPts3dFile(fin7);

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
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
   
   s2sci(3);

   s2sch(0.2);
   s2pt(Pts1.ns,Pts1.xs,Pts1.ys,Pts1.zs,4);
//   s2pt(1,Pts1.xs,Pts1.ys,Pts1.zs,4);
   s2sci(7);
   s2pt(Pts2.ns,Pts2.xs,Pts2.ys,Pts2.zs,4);
   s2pt(10000,Pts6.xs,Pts6.ys,Pts6.zs,1); 
//   s2pt(1,Pts2.xs,Pts2.ys,Pts2.zs,4);
   s2sci(8);
   s2pt(Pts3.ns,Pts3.xs,Pts3.ys,Pts3.zs,4); 
   s2sch(0.6);
   s2pt(2,Pts3.xs,Pts3.ys,Pts3.zs,4);
   int i=60;
   s2pt1(Pts3.xs[i], Pts3.ys[i], Pts3.zs[i], 4);
   s2sch(0.2);
   s2sci(33);
//   s2line(970,Pts4.xs,Pts4.ys,Pts4.zs);
   s2sch(0.2);
   s2pt(Pts4.ns,Pts4.xs,Pts4.ys,Pts4.zs,4);
   s2sci(1);
   
   s2sch(0.2);
   s2pt(Pts5.ns,Pts5.xs,Pts5.ys,Pts5.zs,4);
   s2sci(32);
   s2pt(Pts7.ns,Pts7.xs,Pts7.ys,Pts7.zs,4); 

   s2sch(0.8);					/* Sets size of most symbols */
		    s2sci(23);
		    s2pt1(0.00349774235244073, 0.258867275197351, 0.0, 4);
		    

   s2show(1);					/* Open the s2plot window */

   
   return 1;
   
   /* ./base_flow_Re1_poinc base_flow_x0_poinc_section_1.dat base_flow_x0_poinc_section_4.dat 
    base_flow_x0_poinc_section_5.dat base_flow_x0_poinc_section_5_extra.dat semi_circle_3d_x0_plane.dat 
    base_flow_x0_poinc_section_4_full_traj.dat base_flow_re1_stag_point_stable_manifolds.dat */
}
