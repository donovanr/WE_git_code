#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "const.h"
#include "types.h" 
#include "extern.h"  
#include "WE_main.h"

void Assign() {
  int i,j,Tb,n,m;
  int checkA,checkB;
  char filename[256],sfilename[256],buffer[256];
  FILE *fp;

  for (i=1;i<(nbin+1);i++) {
    tmpnpar[i]=0;
  }

  n=0; //how many particles arrives in start B
  for (i=1;i<(nbin+1);i++) {
    for (j=1;j<(npar[i]+1);j++) {
      if (par[i][j].prob!=0) {
				checkB=Check_State_B(i,j); //check whether it arrives in state B
				if (checkB==1) {
					n+=1;
					Tb=isnapshot-par[i][j].tb0;
					
					sprintf(filename,"successful_trajectories/Trajectory-%d-%d",isnapshot,n);
					fp=fopen(filename, "w");
					fprintf(fp, "%e", (double)(rx_states[par[i][j].numb-1][1])); //TODO replace with print state function
					prob_success += par[i][j].prob;
					free(rx_states[par[i][j].numb-1]);
					rx_states[par[i][j].numb-1]=(int *)malloc(nspecies*sizeof(int));
			
					Fava[0]+=1;
					Fava[Fava[0]]=par[i][j].numb;
					fclose(fp);
				}
				else {
					checkA=Check_State_A(i,j); //check whether it gets back to state A
					if (checkA==1) {  //if it gtes back to state A
						par[i][j].tb0=isnapshot; //reset the start time of transition	
					}
				}
			}
			else {
				checkB=0;
			}
			
			if (checkB!=1) {
				if (par[i][j].coord<leftb) {
					m=1;
				}
				else {
					if (par[i][j].coord>rightb) {
						m=nbin;
					}
					else {
						m=floor((par[i][j].coord-leftb)/wbin)+2;
					}
				}
				tmpnpar[m]+=1;
				tmppar[m][tmpnpar[m]].prob=par[i][j].prob; //keep all the information in the temporary array
				tmppar[m][tmpnpar[m]].coord=par[i][j].coord;
				tmppar[m][tmpnpar[m]].distA=par[i][j].distA;
				tmppar[m][tmpnpar[m]].distB=par[i][j].distB;
				tmppar[m][tmpnpar[m]].tb0=par[i][j].tb0;
				tmppar[m][tmpnpar[m]].numb=par[i][j].numb;
      }
    }
  }
  return;
}
