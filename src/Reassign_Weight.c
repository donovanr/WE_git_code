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

void Reassign_Weight() {
  int i,j;
  int is,id;
  double sumprob,maxprob,minprob;

  for (i=1;i<(nbin+1);i++) {
    if (tmpnpar[i]!=0) {
      sumprob=0;
      for (j=1;j<(tmpnpar[i]+1);j++) {
        sumprob+=tmppar[i][j].prob;
      }
      if (sumprob!=0) {
        maxprob=sumprob/npar[i]*sqrt(mmratio);
        minprob=sumprob/npar[i]/sqrt(mmratio);
        Min1(i);
        while (tmppar[i][tmpnpar[i]].prob<minprob) {
          Min2(i);
          COMB(i);
          Min1(i);
        }
        Max(i);
        while (tmppar[i][1].prob>maxprob) {
          SPLIT(i);
          Max(i);
        }
        while (tmpnpar[i]>npar[i]) {
          Min1(i);
          Min2(i);
          COMB(i);
        }
        while (tmpnpar[i]<npar[i]) {
          Max(i);
          SPLIT(i);
        }
        for (j=1;j<(npar[i]+1);j++) {
          par[i][j].prob=tmppar[i][j].prob;
          par[i][j].coord=tmppar[i][j].coord;
          par[i][j].numb=tmppar[i][j].numb;
          par[i][j].tb0=tmppar[i][j].tb0;
          par[i][j].distA=tmppar[i][j].distA;
          par[i][j].distB=tmppar[i][j].distB;
        }
      }
    }
    else {
      for (j=1;j<(npar[i]+1);j++) {
        if (Fava[0]!=0) {
          par[i][j].numb=Fava[Fava[0]];
          Fava[0]-=1;
        }
        else {
          Fexc[0].i+=1;
          Fexc[0].j+=1;
          Fexc[Fexc[0].i].i=i;
          Fexc[Fexc[0].i].j=j;
          par[i][j].numb=Fexc[0].i+nallpar;
        }
       }
      Make_Ghost(i);
    }
  }

  while(Fexc[0].i!=0) {
    if (Fexc[0].i!=Fava[0]) {
      printf("Fava=%d\tFexc=%d!\n",Fava[0],Fexc[0].i);
      for (j=1;j<(Fava[0]+1);j++) {
        printf("Fava[%d]=%d\n",j,Fava[j]);
      }
      printf("Something is wrong!\n");
      exit(1);
    }
    is=Fexc[0].i;
    id=Fava[is];
    par[Fexc[is].i][Fexc[is].j].numb=id;
    is+=nallpar;
    free(rx_states[id-1]);
    rx_states[id-1]=(int *)malloc(nspecies*sizeof(int));
    memcpy(rx_states[id-1],rx_states[is-1],nspecies*sizeof(int));
    free(rx_states[is-1]);
    rx_states[is-1]=(int *)malloc(nspecies*sizeof(int));

    Fexc[0].i-=1;
    Fexc[0].j-=1;
    Fava[0]-=1;
  }
  return;
}

