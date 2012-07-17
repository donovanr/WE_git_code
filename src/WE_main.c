#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

int main(int argc, char *argv[]) {
  int i,j,k,nsnapshot;
  FILE *fin;

  fin = fopen(argv[1], "r");
    
  fscanf (fin,"%s",bngl_name);
  fscanf (fin,"%d",&coord_ind);			// species index of progress coordinate (starts at 0)
  fprintf (stderr, "Prog Coord: %d\n", coord_ind);
  fscanf (fin,"%lf",&leftb);    		// the position of right boardary of state A
  fscanf (fin,"%lf",&rightb);   		// the position of left boardary of state B
  fscanf (fin,"%d",&nbin);    			// bins
  fscanf (fin,"%d",&nallpar);    		// number of all particles 
  fscanf (fin,"%d",&nsnapshot); 		//how many snapshots
  fscanf (fin,"%lf",&mmratio); 			//ratio of maximum and minimum  probability
  fscanf (fin,"%lf",&startstate);
  fscanf (fin,"%lf",&endstate);
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

    BF_Sim(); 	    //Brute force simulations
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
//  system("rm -r BNGSim/");
}

