#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

#define SPECIES_NAME_LEN 20

void Put_Ini_Stru() {
  int i,j,k;
  FILE *fp;
  char filename[256],buffer[256],c;
  double tmpcoord, tmpdistA, tmpdistB;
  //kuwahara in_state;
  int *in_state;
  double flin;
  
  
  
  // gdat stuff
  //chdir("DATA/");
  //sprintf(buffer,"cat ../BNGSim/initial-gdat | awk 'NR==2 {print $2}' > outputG");
  //system(buffer);
  //system("wait");
	
  //fp=fopen("outputG","r");
  //fscanf(fp,"%lf",&tmpcoord);
  //fclose(fp)
  fp=fopen("BNGSim/initial-gdat","r");
  while((c=fgetc(fp)) != '\n') {} //skip line (header)
  for(k=0; k < coord_ind; k++){
    fscanf(fp, "%*e");
  }
  fscanf(fp, "%lf",&tmpcoord); //only read the value at coord_ind
  fclose(fp);
  //system("rm outputG");
  //chdir("../");

  
  // ffuts tadg
	

  nspecies = 0;
  fp=fopen("BNGSim/initial-species", "r");
  fscanf(fp,"%*s %*s");
  while(fscanf(fp, "%d %*s %*e", &k)){
    nspecies++;
  }
  fprintf(stderr, "found %d species!\n", nspecies);
  fclose(fp);

  //Allocate all particles
  //TODO: find more efficient way to do this
  for(k = 0; k < nallpar; k++) {
    rx_states[k]=(int *)malloc(nspecies*sizeof(int));
  }

  species_names=(char *)malloc(nspecies*sizeof(char *));
  in_state=(int *)malloc(nspecies*sizeof(int));
  fp=fopen("BNGSim/initial-species", "r");
  fscanf(fp,"%*s %*s");
  for(k = 0; k < nspecies; k++){
    species_names[k]=(char *)malloc(SPECIES_NAME_LEN*sizeof(char));
    fscanf(fp, "%*d %s %lf",species_names[k],&flin);
    in_state[k] = (int)flin;
    fprintf(stderr, "Read %s = %e\n", species_names[k], (double)in_state[k]);
  }
  fclose(fp);

	// gdat stuff
  ////tmpcoord = (double)(in_state[coord_ind]); // IMPORTANT, this is the species we're going to look at
 	// ffuts tadg

  tmpdistA=fabs(startstate-tmpcoord);
  tmpdistB=fabs(endstate-tmpcoord);

  if (tmpcoord<leftb) {
    i=1;
  }
  else {
    if (tmpcoord>rightb) {
      i=nbin;
    }
    else {
      i=floor((tmpcoord-leftb)/wbin)+2;
    }
  }

  for (j=1;j<(npar[i]+1);j++) {
    par[i][j].coord=tmpcoord;
    par[i][j].distA=tmpdistA;
    par[i][j].distB=tmpdistB;
    par[i][j].prob=1.0/npar[i];
    par[i][j].tb0=0;
    assert(par[i][j].numb<=nallpar);
    memcpy(rx_states[par[i][j].numb-1], in_state, nspecies*sizeof(int));
    
    // gdat stuff are these files ever used?? everything should already
    // be stored in the par.coord
    //sprintf(filename,"gdat-%d",par[i][j].numb);
    //sprintf(buffer,"cp BNGSim/initial-gdat DATA/%s",filename);
    //system(buffer);
   
    //sprintf(filename,"Trajectory-%d",par[i][j].numb);
    //sprintf(buffer,"cp BNGSim/initial-gdat DATA/%s",filename);
    //system(buffer);
    // ffuts tadg

  }

  free(in_state);
  return;
}
