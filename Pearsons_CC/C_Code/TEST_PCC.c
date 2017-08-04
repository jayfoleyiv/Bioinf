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

    // There are 9 columns in the data set
    // column 1 is the integer associated with the experiment
    // column 2 is the string describing the protein being measured (i think)
    // column 3 is the baseline expression level
    // column 4-9 are the expression levels at times after treatment
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

  printf("  TESTING PCC WITH TWO RANDOM DATA SETS  \n\n\n");
  int ri = rand() % N;
  int rj = rand() % N;

  printf("  Data set 1:\n");
  for (j=0; j<7; j++) {
    printf(" %f ",G[ri*7+j]);
  }
  printf("\n\n  Data set 2:\n");
  for (j=0; j<7; j++) {
    printf(" %f ",G[rj*7+j]);
  }
   
 
    

  double P = S_X_Y( ri, rj, G);
  printf("\n\n  PC between 1 and 2 is %f\n",P);


  printf("\n\n\n  TESTING PCC WITH THE SAME DATA SETS  \n\n\n");
  
  ri = rand() % N;
  rj = ri;

  printf("  Data set 1:\n");
  for (j=0; j<7; j++) {
    printf(" %f ",G[ri*7+j]);
  }
  printf("\n\n  Data set 2:\n");
  for (j=0; j<7; j++) {
    printf(" %f ",G[rj*7+j]);
  }
   
 
    

  P = S_X_Y( ri, rj, G);
  printf("\n\n  PC between 1 and 2 is %f\n",P);


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
