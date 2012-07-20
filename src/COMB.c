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

void COMB(int i) {
  int is,id;
  double p;
  double ran;

  if ((tmppar[i][tmpnpar[i]].prob+tmppar[i][(tmpnpar[i]-1)].prob)!=0) {
    p=tmppar[i][tmpnpar[i]].prob/(tmppar[i][tmpnpar[i]].prob+tmppar[i][(tmpnpar[i]-1)].prob);
  }
  else {
    p=0;
  }
  ran=rand()/2147483647.0;

  if (ran<p) { /* keep the last one */
    if (tmppar[i][(tmpnpar[i]-1)].numb<=nallpar) {
      Fava[0]+=1;
      Fava[Fava[0]]=tmppar[i][(tmpnpar[i]-1)].numb;
    }
    else {
      if ((tmppar[i][(tmpnpar[i]-1)].numb-nallpar)!=Fexc[0].i) { /* not last one */
				is=tmppar[Fexc[Fexc[0].i].i][Fexc[Fexc[0].i].j].numb;
				id=tmppar[i][(tmpnpar[i]-1)].numb;
				tmppar[Fexc[Fexc[0].i].i][Fexc[Fexc[0].i].j].numb=tmppar[i][(tmpnpar[i]-1)].numb;
        free(rx_states[id-1]);
				rx_states[id-1]=(int *)malloc(nspecies*sizeof(int));
        memcpy(rx_states[id-1], rx_states[is-1], nspecies*sizeof(int));
        free(rx_states[is-1]);
				rx_states[is-1]=(int *)malloc(nspecies*sizeof(int));

				Fexc[tmppar[i][(tmpnpar[i]-1)].numb-nallpar].i=Fexc[Fexc[0].i].i;
				Fexc[tmppar[i][(tmpnpar[i]-1)].numb-nallpar].j=Fexc[Fexc[0].i].j;
      }
      Fexc[0].i-=1;
      Fexc[0].j-=1;
    }
    tmppar[i][(tmpnpar[i]-1)].coord=tmppar[i][tmpnpar[i]].coord;
    tmppar[i][(tmpnpar[i]-1)].tb0=tmppar[i][tmpnpar[i]].tb0;
    tmppar[i][(tmpnpar[i]-1)].numb=tmppar[i][tmpnpar[i]].numb;
    tmppar[i][(tmpnpar[i]-1)].distA=tmppar[i][tmpnpar[i]].distA;
    tmppar[i][(tmpnpar[i]-1)].distB=tmppar[i][tmpnpar[i]].distB;
  }

  else { /* throw away the last one */
    if (tmppar[i][tmpnpar[i]].numb<=nallpar) {
      Fava[0]+=1;
      Fava[Fava[0]]=tmppar[i][tmpnpar[i]].numb;
    }
    else {
      if ((tmppar[i][tmpnpar[i]].numb-nallpar)!=Fexc[0].i) {
				is=tmppar[Fexc[Fexc[0].i].i][Fexc[Fexc[0].i].j].numb;
				id=tmppar[i][tmpnpar[i]].numb;
				tmppar[Fexc[Fexc[0].i].i][Fexc[Fexc[0].i].j].numb=tmppar[i][tmpnpar[i]].numb;
        free(rx_states[id-1]);
				rx_states[id-1]= (int *)malloc(nspecies*sizeof(int));
        memcpy(rx_states[id-1],rx_states[is-1],nspecies*sizeof(int));
        free(rx_states[is-1]);
				rx_states[is-1] = (int *)malloc(nspecies*sizeof(int));

				Fexc[tmppar[i][tmpnpar[i]].numb-nallpar].i=Fexc[Fexc[0].i].i;
				Fexc[tmppar[i][tmpnpar[i]].numb-nallpar].j=Fexc[Fexc[0].i].j;
      }
      Fexc[0].i-=1;
      Fexc[0].j-=1;
    }
  }

  tmppar[i][(tmpnpar[i]-1)].prob+=tmppar[i][tmpnpar[i]].prob;

  tmpnpar[i]-=1;

  return;
}
