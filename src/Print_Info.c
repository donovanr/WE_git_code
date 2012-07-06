#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

void Print_Info() {
  int i,j;

  printf ("************************\n");
  printf ("snapshot\t%d\n",isnapshot);
  printf ("************************\n");
  for (i=1;i<(nbin+1);i++) {
    for (j=1;j<(npar[i]+1);j++) {
      printf("bin=%04d\tpar=%03d\tcoord=%05.1lf\tprob=%01.14le\tdistA=%05.1lf\tdistB=%05.1lf\tprob_success=%01.14le\n",
             i,j,par[i][j].coord,par[i][j].prob,par[i][j].distA,par[i][j].distB,prob_success);
    }
  }
  return;
}
