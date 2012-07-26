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

int main(int argc, char *argv[]) {
  int i,nsnapshot;
  FILE *fin;

  fin = fopen(argv[1], "r");
    
  fscanf (fin,"%*s %s",bngl_name);      /* name of the system - needs to be the same as the name of the bngl file */
  fscanf (fin,"%*s %d",&recycling_bit); /* whether or not to recycle probability back to state A when it reaches the state B */
  fscanf (fin,"%*s %d",&coord_ind);     /* species index of progress coordinate (starts at 0) */
  fprintf (stderr, "Prog Coord: %d\n", coord_ind);
  fscanf (fin,"%*s %lf",&leftb);        /* the position of right boarder of state A */
  fscanf (fin,"%*s %lf",&rightb);       /* the position of left boarder of state B */
  fscanf (fin,"%*s %d",&nbin);          /* bins */
  fscanf (fin,"%*s %d",&nallpar);       /* number of all particles */
  fscanf (fin,"%*s %d",&nsnapshot);     /* how many snapshots */
  fscanf (fin,"%*s %lf",&mmratio);      /* ratio of maximum and minimum  probability */
  fscanf (fin,"%*s %lf",&startstate);
  fscanf (fin,"%*s %lf",&endstate);
  state_size = nallpar + BLOCK_SIZE;
  prob_success = 0;
  rx_states = malloc(state_size * sizeof(int*));
  
  fprintf(stderr,"Initial...\n");
  Initial();
  isnapshot=0;
  fprintf(stderr,"Print_Info...\n");
  Print_Info();
  while (isnapshot<nsnapshot) {

    fprintf(stderr, "snapshot: %d\n", isnapshot);
    fprintf(stderr,"BF_Sim...\n");

    BF_Sim();
    fprintf(stderr,"Cal_Dist_Coord...\n");
    Cal_Dist_Coord();
    isnapshot+=1;
    fprintf(stderr,"Assign...\n");
    Assign();
    fprintf(stderr,"Reassign...\n");
    Reassign_Weight();
    fprintf(stderr,"Print_Info...\n");
    Print_Info();
  }

 
  for(i = 0; i < state_size; i++){
    if(rx_states[i] != NULL) {
      free(rx_states[i]);
    }
  }
  free(rx_states);
  system("rm -r BNGSim/ 2>/dev/null");
  
  return 0;
}

