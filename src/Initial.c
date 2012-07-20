#include <math.h>
#include <stdio.h>
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

void Initial() {
  int i,j;
  int stime; /* for random seed */
  long ltime; /* for random seed */
  int np;

  system("mkdir successful_trajectories 2>/dev/null");
  
  system("rm -r BNGSim 2>/dev/null");
  system("mkdir BNGSim 2>/dev/null");
  
  system("cp bng_scripts/*.sh BNGSim/");
  system("chmod +x BNGSim/*.sh");
    
  chdir("BNGSim/");
  sprintf(buffer, "cp ../input/%s.bngl %s.bngl", bngl_name, bngl_name);
  system(buffer);
  
  sprintf(buffer, "./initialrun.sh %s.bngl", bngl_name);
  system(buffer);  
  
  chdir("../");

  Fava[0]=0;
  Fexc[0].i=0;
  Fexc[0].j=0;

  wbin=(rightb-leftb)/(nbin-2); 
  npar[nbin]=nallpar/nbin;  /* at first just use the average for npar[nbin] */

  for (i=1;i<(nbin);i++) {
    pbin[i]=leftb+wbin*(i-1); /* the postions of bars using to separate the whole space, start from 1, end at (nbin-1) */
    npar[i]=npar[nbin];
  }

  ltime = time(NULL);  /* reset the random seed by using the system time */
  stime = (unsigned) ltime/2;
  srand(stime);

  np=0;
  for (i=1;i<(nbin+1);i++) {
    for (j=1;j<(npar[i]+1);j++) {
      np+=1;
      par[i][j].numb=np;
    }
    Make_Ghost(i);
  }

  Put_Ini_Stru();

  return;
}

