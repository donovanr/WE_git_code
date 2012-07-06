#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "const.h"
#include "types.h"
#include "extern.h"
#include "WE_main.h"

void BF_Sim() {
  int i,j,k;
  char filename[256],buffer[256];
  FILE* fp;
  int* cur_state;
  double flin;

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

				// gdat stuff
        system("cat parameters spec_State reactions groups > my_State");
        // ffuts tadg

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
				
				// gdat stuff
				sprintf(filename,"gdat-%d",par[i][j].numb);
				sprintf(buffer,"mv %s.gdat ../DATA/%s",bngl_name,filename); 
				system(buffer);
				// ffuts tadg

      }
    }
  }
  chdir("..");
  return;
}
