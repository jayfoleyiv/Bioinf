#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

double S_X_Y(int idx, int jidx, double *G);
double PhiG(int idx, double *G);
int main() {

  srand(time(NULL));

  int i, j;
  int N;
  FILE *fp;
  /*
  // MMP1 - Gene 840
  double g840[] = {0.855,   0.505,   -0.782,  0.525,   -0.585,  -0.179,  -0.253  };
  // EMP46 - Gene 841
  double g841[] = {-1.051,  -1.138,  -0.401,  -0.377,  0.663,   1.041,   -0.205  };

  N = 6;

  double G[1000][10];
  */

  char   *line;
  double *G;

  G  = (double *) malloc(8*10000*sizeof(double));
  line = (char *) malloc(10000*sizeof(char));
  fp = fopen("../DATA_FILES/Data_Try_Small_Subset.txt","r");


  // Just reading the data here!
  i=0;
  do {

    for (j=0; j<9; j++) {
   
      fscanf(fp,"%s",line);
      if (j>1) {
     
        G[i*7+(j-2)] = atof(line);

      }
   
    }
    i++;

  }while(!feof(fp));

  // Just printing out the data here to confirm it was read!
  N = i-1;

  for (i=0; i<N; i++) {

    for (j=0; j<7; j++) {

      //printf(" %f ",G[i*7+j]);
    
    }
    //printf("\n");
 }

 double bin[] = {-0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.1 };
 double f[] = {0.0, 00.0, 0.0, 00.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

 // Using a while loop because we want to make sure
 // we aren't comparing the same vectors in the analysis... 
 int pcc_count = 0;
 while (pcc_count<10000) {
 //for (i=0; i<10000; i++) {

   int ri = rand() % N;
   int rj = rand() % N;

   if (ri != rj) {

     double P = S_X_Y( ri, rj, G);
     printf("  PC between %i and %i is %f\n",ri,rj,P);

     int j=0; 
     int die = 1;
     do {

       if (bin[j]>P) {

         die=0;
         f[j] += 1;  
  
       }

       else if (j==19) {
 
         die = 0;
         f[j] += 1;

       }

       j++;

     }while(die);

   pcc_count++;

   }

 }
 
 for (i=0; i<20; i++) {

   printf("  %f  %12.10f  \n",bin[i],f[i]);

 }

/*
  double PhiX, PhiY;
  PhiX = 0.;
  PhiY = 0.; 
  // Compute phi_g840 here!
  for (i=1; i<= N; i++) {

     PhiX += (G[r1][i] - G[r1][0])*(G[r1][i] - G[r1][0]);
     PhiY += (G[r2][i] - G[r2][0])*(G[r2][i] - G[r2][0]);


   //  PhiX += (g840[i] - g840[0])*(g840[i] - g840[0]);
   // PhiY += (g841[i] - g841[0])*(g841[i] - g841[0]); 

  }

  PhiX = PhiX/N;
  PhiY = PhiY/N;

  PhiX = sqrt(PhiX);
  PhiY = sqrt(PhiY);

  printf("  PhiX is %f\n",PhiX);
  printf("  PhiY is %f\n",PhiY);
    //printf("  Expression level of Gene 840 at t=%i is  %f\n",i,g840[i]);
    //printf("  Expression level of Gene 841 at t=%i is  %f\n",i,g841[i]);
*/

  return 0;

}


double PhiG(int idx, double *G) {
  int i;
  double Goffset = G[idx*7];
  double diff, sum;

  printf("  Goffset is %f\n",Goffset);
  sum = 0.;
  for (i=1; i<7; i++) {
  
    diff = G[idx*7+i] - Goffset;
    printf("  diff is %f\n",diff);
    diff *= diff;
    sum += diff;
  }

  printf("  phi is %f\n",sum/6.);
  return sqrt(sum/6.);

}

double S_X_Y(int idx, int jidx, double *G) {
  int i;
  double phix, phiy, diffx, diffy;
  double Xoffset, Yoffset, sum;

  phix = PhiG(idx, G); 
  phiy = PhiG(jidx, G);

  Xoffset = G[idx*7];
  Yoffset = G[jidx*7];

  sum = 0.;
  for (i=0; i<7; i++) {

    diffx = G[idx*7+i] - Xoffset;
    diffy = G[jidx*7+i] - Yoffset;
    
    sum += (diffx/phix)*(diffy/phiy);
  

  }

  return sum/6.;
}
