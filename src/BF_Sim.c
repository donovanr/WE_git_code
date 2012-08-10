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

void BF_Sim() {
  int i,j,k;
  char buffer[256],c;
  FILE* fp;
  int* cur_state;
  double flin,tmpcoord;

  chdir("BNGSim/");
  sprintf(buffer, ". setparameters.sh %s.bngl", bngl_name);
  system(buffer);
  for (i=1;i<(nbin+1);i++) {
    for (j=1;j<(npar[i]+1);j++) {
      if (par[i][j].prob!=0) {

        cur_state = rx_states[par[i][j].numb-1];

        fp=fopen("spec_State", "w");
        fprintf(fp,"begin species\n");

        for(k = 0; k < nspecies; k++){
          fprintf(fp, " %d %s %e\n", k+1, species_names[k], (double)cur_state[k]);
        }
        fprintf(fp,"end species\n");
        fclose(fp);        
        
        /* just use template net file -- insert new species; template already composed so as to lack species block. */
        
        /* insert current spec_State species into template net file after molecule types block and save as new .net file*/
        sprintf(buffer, "sed '/end molecule types/r spec_State' template_no_species.net > %s.net", bngl_name);
        system(buffer);
        system("wait");
                
        sprintf(buffer, "./restart.sh");  
        system(buffer);
        sprintf(buffer, "sed -n '/begin species/,/end species/w newspecies' %s_end.net", bngl_name);
        system(buffer);

        fp=fopen("newspecies", "r");
         fscanf(fp,"%*s %*s");
        for(k = 0; k < nspecies; k++){
          fscanf(fp, "%*d %*s %lf",&flin);
          cur_state[k] = (int)flin;
        }
        fclose(fp);
  

        /* just set particle coordinate here instead of in Cal_Dist_Coord */
        sprintf(buffer,"%s.gdat",bngl_name); 
        fopen(buffer, "r");
        while((c=fgetc(fp)) != '\n') {} /* skip header */
        while((c=fgetc(fp)) != '\n') {} /* skip first line of data */
        for(k=0; k < coord_ind; k++){
          fscanf(fp, "%*e");
        }
        fscanf(fp, "%lf",&tmpcoord); /* only read the value at coord_ind */
        fclose(fp);
        par[i][j].coord = tmpcoord;        
      }
    }
  }
  chdir("..");
  return;
}
