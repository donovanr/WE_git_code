#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

void Cal_Dist_Coord() {
  int i,j;

  for (i=1;i<(nbin+1);i++) {
    for (j=1;j<(npar[i]+1);j++) {
      if (par[i][j].prob!=0) {
        
        par[i][j].distA=fabs(startstate-par[i][j].coord);
        par[i][j].distB=fabs(endstate-par[i][j].coord);
      
      }
    }
  }
  return;
}
