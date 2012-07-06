#include <math.h>
#include <stdio.h>
#include <string.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

void Min1(int i) {
  int j,m;
  //void Switch(int i, int j, int k);

  m=1;
  for (j=2;j<(tmpnpar[i]+1);j++) {
    if (tmppar[i][j].prob<tmppar[i][m].prob) {
      m=j;
    }
  }
  if (m!=tmpnpar[i]) {
    Switch(i,m,tmpnpar[i]);
  }
  return;
}
