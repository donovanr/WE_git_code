#include <math.h>
#include <stdio.h>
#include <string.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

void Cal_Dist_Coord() {
  int i,j;
  FILE *fp;
  char filename[256],buffer[256];
  double tmpcoord;

  //chdir("DATA/");
  for (i=1;i<(nbin+1);i++) {
    for (j=1;j<(npar[i]+1);j++) {
      if (par[i][j].prob!=0) {
        
        // tmpcoord=(double)(rx_states[par[i][j].numb-1][coord_ind]);
				
	// gdat stuff
	//sprintf(filename,"gdat-%d",par[i][j].numb);
	//sprintf(buffer,"cat ../DATA/%s | awk 'NR==3 {print $2}' > outputG",filename);
	//system(buffer);
	//system("wait");				
	
	//fp=fopen("outputG","r");
	//fscanf(fp,"%le",&tmpcoord);
	//fclose(fp);
	// ffuts tadg
				
	par[i][j].distA=fabs(startstate-par[i][j].coord);
	par[i][j].distB=fabs(endstate-par[i][j].coord);
			
	//par[i][j].coord=tmpcoord;
      }
    }
  }
  //system("wait"); //just incase
  //system("rm outputG");
  //chdir("../");
  return;
}
