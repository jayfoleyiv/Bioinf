#include<stdlib.h>
#include<math.h>
#include<stdio.h>


double S_X_Y(int idx, int jidx, double *G, int dim);
double PhiG(int idx, double *G, int dim);
void ComputeRank(double *numbers, double * rank, int n);
int main() {

  FILE *fp;
  char *line;

  // array for data and ranked data
  double *tD, *tRD, *D, *rD;

  line = (char *)malloc(1000*sizeof(char));
  D    = (double *)malloc(8*12*sizeof(double));
  rD   = (double *)malloc(8*12*sizeof(double));
  tD   = (double *)malloc(8*sizeof(double));
  tRD  = (double *)malloc(8*sizeof(double));


  fp = fopen("Sample.txt","r");

  // Read 12 lines of data from Sample.txt
  for (int i=0; i<12; i++) {

    // First column of each row is the gene label, then there are 7 columns of data 
    for (int j=0; j<8; j++) {

      // read everything like a string
      fscanf(fp,"%s",line);
      if (j>0) {
      
        // convert the string data to a double when it makes sense to do so (all but first column)
        D[i*7+(j-1)] = atof(line);
 
      }

    }
  }

  // Go through a very stupid procedure to rank each expression level
  for (int i=0; i<12; i++) {

    // Copy current data set to temp array
    for (int j=0; j<7; j++) {

      tD[j] = D[i*7+j];
      tRD[j] = 0.;
    }  
    // Rank current data set
    ComputeRank(tD, tRD, 7);

    //  Now copy ranks to permanent array
    for (int j=0; j<7; j++) {
 
      rD[i*7+j] = tRD[j];
  
    }

  }

  // Just check to make sure things are ranked!
  for (int i=0; i<12; i++) {

    for (int j=0; j<7; j++) {
 
      printf("  %f  ",D[i*7+j]);
      printf("  %f  \n",rD[i*7+j]);
    }
    printf("\n");
  }

  // Now compute Spearman's CC between each gene with it's NN in the dataset (gene i and gene i+1)
  for (int i=0; i<11; i++) {

    double SCC = S_X_Y(i, i+1, rD, 7);
    printf("  SCC BETWEEN %i and %i is %f\n",i,i+1,SCC);

  }

   

}


// Function to rank data stored in the array "numbers" and store the ranks in the array "rank".  
// Length of the array to be ranked, and length of the rank array, should both be n
void ComputeRank(double *numbers, double * rank, int n) {
    
    for(int i = 0; i < n; i++) {
        int curRank = 1;
        
        // We assume the rank of numbers[0...i-1] is already computed.
        // Now if we add a[i] to list, we need to update the ranks.
        for (int j = 0; j < i; j++) {
            
            if (numbers[i] > numbers[j]) { // Update rank of numbers[i]
                curRank++;
            } 
            else { // A number smaller than numbers[j] has appeared. Update rank of numbers[j]
                rank[j]+=1;
            }
        }
      
        rank[i] = (double)curRank;
    }
}
// Gets the Standard Deviation of the data stored in the array "G" (which should be the ranked values)
// dim is the number of ranked values and idx+1 is the gene number... i.e. idx=0 is the first
// gene from the data set, idx=1 is the second gene from the data set, etc
double PhiG(int idx, double *G, int dim) {
  int i;
  double Goffset;  // Mean value of ranked data set
  double diff, sum;

  // Calculate the mean of the ranked values for gene idx+1
  Goffset=0.;
  for (i=0; i<dim; i++) {

    Goffset +=  G[idx*dim+i]; 

  }
  Goffset /= dim;

  sum = 0.;
  for (i=0; i<dim; i++) {
  
    diff = G[idx*dim+i] - Goffset;
    diff *= diff;
    sum += diff;
  }

  // stdev of the ranked values for gene idx+1
  return sqrt(sum/dim);

}

// Calculates the SCC between ranked genes idx+1 and jidx+1 stored in the array G... that is
// idx=0 would be the first gene in the dataset and jidx=3 would be the fourth gene in the dataset.
// dim is the number of ranked expression levels in the dataset.
double S_X_Y(int idx, int jidx, double *G, int dim) {
  int i;
  double phix, phiy, diffx, diffy;
  double Xoffset, Yoffset, sum;

  phix = PhiG(idx, G, dim); 
  phiy = PhiG(jidx, G, dim);


  // Mean of the ranked datasets... note that it is redundant to compute this for each
  // ranked dataset if they contain the same number of datapoints, but we will do it anyway bc it
  // is not exactly expensive to do so!
  Xoffset = 0.;
  Yoffset = 0.; 

  for (i=0; i<dim; i++) {

    Xoffset += G[idx*dim+i];
    Yoffset += G[jidx*dim+i];

  }
  Xoffset /= dim;
  Yoffset /= dim;

  sum = 0.;
  for (i=0; i<dim; i++) {

    diffx = G[idx*dim+i] - Xoffset;
    diffy = G[jidx*dim+i] - Yoffset;
    
    sum += (diffx/phix)*(diffy/phiy);
  

  }
  // SCC of ranked expression levels for gene idx+1 and gene jidx+1
  return sum/dim;
}
