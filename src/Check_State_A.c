#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "const.h"
#include "types.h"
#include "extern.h"
#include "WE_main.h"

int Check_State_A(int i, int j) {
  int m;
  double R,dist;

  R=fabs(startstate-endstate);
  dist=par[i][j].distB;
  if (dist>=R) {
    m=1;
  }
  else {
    m=0;
  }
  return(m);
}

