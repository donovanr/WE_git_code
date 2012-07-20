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

void Switch(int i, int j, int k) {
  int tmptb0,tmpnumb;
  double tmpcoord,tmpdistA,tmpdistB;
  double tmpprob;

  tmpprob=tmppar[i][j].prob;
  tmppar[i][j].prob=tmppar[i][k].prob;
  tmppar[i][k].prob=tmpprob;

  tmpcoord=tmppar[i][j].coord;
  tmppar[i][j].coord=tmppar[i][k].coord;
  tmppar[i][k].coord=tmpcoord;

  tmptb0=tmppar[i][j].tb0;
  tmppar[i][j].tb0=tmppar[i][k].tb0;
  tmppar[i][k].tb0=tmptb0;

  tmpdistA=tmppar[i][j].distA;
  tmppar[i][j].distA=tmppar[i][k].distA;
  tmppar[i][k].distA=tmpdistA;

  tmpdistB=tmppar[i][j].distB;
  tmppar[i][j].distB=tmppar[i][k].distB;
  tmppar[i][k].distB=tmpdistB;

  if (tmppar[i][j].numb>nallpar) {
    Fexc[tmppar[i][j].numb-nallpar].j=k;
  }
  if (tmppar[i][k].numb>nallpar) {
    Fexc[tmppar[i][k].numb-nallpar].j=j;
  }
  tmpnumb=tmppar[i][j].numb;
  tmppar[i][j].numb=tmppar[i][k].numb;
  tmppar[i][k].numb=tmpnumb;

  return;
}
