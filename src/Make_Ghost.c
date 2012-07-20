#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

void Make_Ghost(int i) {
  int j;
  char filename[256],buffer[256];
  double tmpcoord;

  if (i==nbin) {
    tmpcoord=pbin[nbin-1]+0.5*wbin;
  }
  else {
    tmpcoord=pbin[i]-0.5*wbin;
  }
  for (j=1;j<(npar[i]+1);j++) {
    par[i][j].coord=tmpcoord;
    par[i][j].prob=0;
    par[i][j].tb0=0;
    par[i][j].distA=0;
    par[i][j].distB=0;
    free(rx_states[par[i][j].numb-1]);
    rx_states[par[i][j].numb-1]=(int *)malloc(nspecies*sizeof(int));
  }
  return;
}
