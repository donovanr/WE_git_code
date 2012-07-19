#include <math.h>
#include <stdio.h>
#include <string.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

void SPLIT(int i) {
  int j;
  size_t new_state_size;
  char filename[256],sfilename[256],buffer[256];

  tmpnpar[i]+=1;
  tmppar[i][1].prob=tmppar[i][1].prob/2,0;
  tmppar[i][tmpnpar[i]].prob=tmppar[i][1].prob;
  tmppar[i][tmpnpar[i]].coord=tmppar[i][1].coord;
  tmppar[i][tmpnpar[i]].distA=tmppar[i][1].distA;
  tmppar[i][tmpnpar[i]].distB=tmppar[i][1].distB;
  tmppar[i][tmpnpar[i]].tb0=tmppar[i][1].tb0;

  if (Fava[0]!=0) {
    tmppar[i][tmpnpar[i]].numb=Fava[Fava[0]];
    Fava[0]-=1;
  }
  else {
    Fexc[0].i+=1;
    Fexc[0].j+=1;
    Fexc[Fexc[0].i].i=i;
    Fexc[Fexc[0].i].j=tmpnpar[i];
    tmppar[i][tmpnpar[i]].numb=Fexc[0].i+nallpar;
  }

  new_state_size = state_size;
  //not enough space for tmp particle so make some
  while(tmppar[i][tmpnpar[i]].numb-1 > new_state_size){
    new_state_size += BLOCK_SIZE;
  }

  if(new_state_size != state_size){
    rx_states = realloc(rx_states, new_state_size*sizeof(int*));
    for(j = 0; j <new_state_size-state_size; j++){
      rx_states[state_size+j] = malloc(nspecies*sizeof(int));
    } 
    state_size = new_state_size;
  }

  free(rx_states[tmppar[i][tmpnpar[i]].numb-1]);
  rx_states[tmppar[i][tmpnpar[i]].numb-1]=(int *)malloc(nspecies*sizeof(int));
  memcpy(rx_states[tmppar[i][tmpnpar[i]].numb-1],rx_states[tmppar[i][1].numb-1], nspecies*sizeof(int));

  return;
}


