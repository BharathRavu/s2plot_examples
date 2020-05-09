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
float *x2 = NULL;
float *y2 = NULL;
float *z2 = NULL;
float *stab2 = NULL;
float *grid_iso_val = NULL;
int n = 0;
int n2 = 0;
int n3 = 0;
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

   FILE *fin2 = fopen(argv[2], "r");
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

   FILE *fin3 = fopen(argv[3], "r");
   while (!feof(fin3)) {
     if (fgets(line, 255, fin3)) {
       if (sscanf(line, "%f", &fs) == 1) {
	 if (!(n3 % STEP)) {
		 grid_iso_val = (float *)realloc(grid_iso_val, (n3+STEP) * sizeof(float));
	 }
	 grid_iso_val[n3] = fs;
	 n3++;
       } else {
	 fprintf(stderr, "Couldn't read 1 floats at line %d\n", n3);
	 exit(-1);
       }
     }
   }

   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., 0,1., -1.,1.);		/* Set the window coordinates */
   s2svp(-1,1, 0,1, -1,1);
 /*  s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0); */	/* Draw coordinate box */
   

   pushVRMLname("POINTS");
   s2sch(1);					/* Sets size of most symbols */
 /*  s2sci(S2_PG_BLACK); */
   s2pt(n,x,y,z,symbol);	/* Draw a single point */
   pushVRMLname("LINES");
   s2sch(0.6);
        s2slw(4);					/* Set line width */
   float xx[2], yy[2], zz[2], stbl, xm, ym, zm, xx1[2], yy1[2], zz1[2], xx2[2], yy2[2], zz2[2];

      s2scr(17, 0.0, 1.0, 1.0);
/*      s2scr(18, 1-0.03137254901, 1-0.5725490196, 1-0.81568627451); */ /* inverted electric blue def */	
       s2scr(18, 1, 1, 0);
      s2scr(19, 1.0, 0.0, 1.0);
      s2scr(20, 0.0, 0.0, 1.0);
   int i;				/* Loop variables */

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
		   s2sci(17);
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

		        s2sci(17);
		        s2line(2,xx2,yy2,zz2);

                        }
                    else{

                        s2sci(17);
		        s2line(2,xx1,yy1,zz1);

		        s2sci(18);
		        s2line(2,xx2,yy2,zz2);


                        }
 //                   s2slw(50);					/* Sets size of point */
	
		    s2sci(19);
                    s2pt1(xm, ym, zm, 4);

	   }

   }
 s2sch(1.2);					/* Sets size of most symbols */
		    s2sci(20);
		    s2pt1(0.0, 0.258868542281411, 0.0, 4);

   int j, k;				/* Loop variables */
   int nx, ny, nz;			/* Number of cells in grid */
   float ***grid;			/* Grid data */
   float tr[12];			/* Transformation matrix */
   int resolution;			/* Resolution of isosurface */
   float level;				/* Isosurface level to plot */
   float alpha;				/* Alpha channel */
   char trans;				/* Drawing mode for isosurface */
   int id1;			/* ID for isosurface objects */

   nx = 201; 				/* Grid dimensions */
   ny = 101;
   nz = 201;

  /* Create transpose matrix mapping data indices to world coords */
   tr[0]=tr[8]=-1;
   tr[4]= 0.0;				  /* Offsets */
   tr[1] = tr[6] = tr[11] = 0.01; 			  /* Increments */
   tr[2] = tr[3] = tr[5] = tr[7] = tr[9] = tr[10] = 0.;   /* Cross terms */

   /* allocate and generate the data grid */
   int kk=0;
   grid = (float ***)malloc(nx * sizeof(float **));
   for (i = 0; i < nx; i++) {
      grid[i] = (float **)malloc(ny * sizeof(float *));
      for (j = 0; j < ny; j++) {
         grid[i][j] = (float *)malloc(nz * sizeof(float));
         for (k = 0; k < nz; k++) {
	     grid[i][j][k] = grid_iso_val[kk];
	     kk=kk+1;
         }
      }
   }

   level      = 0.199;			/* Set the isosurface level */
   resolution = 1;			/* Set the isosurface resolution */
   alpha      = 0.5;			/* Set the alpha channel */
   trans      = 's';			/* Opaque isosurface */
   pushVRMLname("Iso_surf");
/* Create the isosurface object */
   id1 = ns2cis(grid, nx, ny, nz, 0, nx-1, 0, ny-1, 0, nz-1,
		   tr, level, resolution, trans, alpha, 0.3, 0.3, 0.3);
   ns2dis(id1, 0);			/* Draw it */


/*   s2slw(2);			*/		/* Set line width */
/*   s2line(n2,x2,y2,z2);  */

   s2show(1);					/* Open the s2plot window */

   
   return 1;
}
